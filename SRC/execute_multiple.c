/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_multiple.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 16:31:14 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/08 18:07:33 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "function.h"
#include "libft.h"

#include <unistd.h> /* execve, dup, close etc. */
#include <stdlib.h> /* malloc */
#include <sys/wait.h> /* wait */
#include <stdio.h> /* perror */
#include <errno.h> /* ECHILD */

static const t_function	g_function[] = {
{"echo", &exec_echo, 1},
{"cd", &exec_cd, 0},
{"pwd", &exec_pwd, 1},
{"export", &exec_export, 0},
{"unset", &exec_unset, 0},
{"env", &exec_env, 1},
{"exit", &exec_exit, 0},
{0, NULL, 0}
};

static int	is_pipe(t_token *tok)
{
	return (tok->token == T_PIPE);
}

/* runs a builtin if it encounters it. */
static void	m_run_builtin(char **args, t_vars *vars)
{
	int	i;

	i = 0;
	while (g_function[i].key != NULL)
	{
		if (ft_strcmp(g_function[i].key, *args) == 0)
		{
			exit(g_function[i].func(vars));
		}
		i++;
	}
}

/* counts amount of elements until f(token) returns 1 */
static size_t	count_upto(t_token *lst, int (*f)(t_token *))
{
	size_t	n;

	n = 0;
	while (lst)
	{
		if (f(lst))
			break ;
		n++;
		lst = lst->next;
	}
	return (n);
}

static char	**create_argv(t_token **lst)
{
	size_t	size;
	size_t	i;
	char	**argv;

	size = count_upto(*lst, &is_pipe);
	argv = malloc((size + 1) * sizeof(char *));
	if (!argv)
		fatal_perror("malloc");
	i = 0;
	while (i < size)
	{
		argv[i] = (*lst)->content;
		i++;
		*lst = (*lst)->next;
	}
	if (*lst)
	{
		*lst = (*lst)->next;
	}
	argv[i] = NULL;
	return (argv);
}

static void	m_proc(int infd, int outfd, char **args, t_vars *vars)
{
	char	*path;

	if (infd != -1)
	{
		close(STDIN_FILENO);
		if (dup(infd) == -1)
			fatal_perror("dup(infd)");
	}
	if (outfd != -1)
	{
		close(STDOUT_FILENO);
		if (dup(outfd) == -1)
			fatal_perror("dup(outfd)");
	}
	m_run_builtin(args, vars);
	path = pathresolve_tryfind(*args, vars->environ);
	if (!path)
		path = "";
	if (execve(path, args, vars->environ) == -1)
	{
		perror(*args);
		exit(127);
	}
}

// I hate this duplicate code
static void	final_proc(int readfd, char **argv, t_vars *vars,
	t_token *old_tlst)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		fatal_perror("fork");
	}
	else if (pid == 0)
	{
		vars->token_list = old_tlst;
		m_proc(readfd, -1, argv, vars);
	}
	free(argv);
}

// TODO: builtins
// TODO: redir
// TODO: perhaps create_argv in m_proc?
void	pipe_next(int readfd, t_token *tlst, t_vars *vars)
{
	int		pfds[2];
	char	**argv;
	pid_t	pid;
	t_token	*old_tlst;

	old_tlst = tlst;
	argv = create_argv(&tlst);
	if (tlst == NULL)
	{
		final_proc(readfd, argv, vars, old_tlst);
		return ;
	}
	if (pipe(pfds) == -1)
		fatal_perror("pipe");
	pid = fork();
	if (pid == -1)
		fatal_perror("fork");
	else if (pid == 0)
	{
		close(pfds[0]);
		vars->token_list = old_tlst;
		m_proc(readfd, pfds[1], argv, vars);
	}
	free(argv);
	close(pfds[1]);
	pipe_next(pfds[0], tlst, vars);
}

// TODO: Return 127 for _the last_ command, not just some race condtion.
int	execute_multiple(t_vars *vars)
{
	pid_t	waitpid;
	int		status;

	pipe_next(-1, vars->token_list, vars);
	while (1)
	{
		waitpid = wait(&status);
		if (waitpid == -1)
		{
			if (errno != ECHILD)
				fatal_perror("wait");
			break ;
		}
		else if (WIFEXITED(status))
		{
			vars->exit_code = WEXITSTATUS(status);
		}
	}
	return (vars->exit_code);
}
