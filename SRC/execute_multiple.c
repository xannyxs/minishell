/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_multiple.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 16:31:14 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/04 12:43:09 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h> /* execve, dup, close etc. */
#include <stdlib.h> /* malloc */
#include <sys/wait.h> /* wait */
#include <errno.h> /* ECHILD */

static int	is_pipe(t_token *tok)
{
	return (tok->token == T_PIPE);
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

// TODO: exit(127)
static void	m_proc(int infd, int outfd, char **args, char **envp)
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
	path = pathresolve_tryfind(*args, envp);
	if (!path)
		path = "";
	if (execve(path, args, envp) == -1)
	{
		fatal_perror(*args);
	}
}

// I hate this duplicate code
static void	final_proc(int readfd, char **argv, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		fatal_perror("fork");
	}
	else if (pid == 0)
	{
		m_proc(readfd, -1, argv, envp);
	}
	free(argv);
}

// TODO: builtins
// TODO: redir
// TODO: perhaps create_argv in m_proc?
void	pipe_next(int readfd, t_token *tlst, char **envp)
{
	int		pfds[2];
	char	**argv;
	pid_t	pid;

	argv = create_argv(&tlst);
	if (tlst == NULL)
	{
		final_proc(readfd, argv, envp);
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
		m_proc(readfd, pfds[1], argv, envp);
	}
	free(argv);
	close(pfds[1]);
	pipe_next(pfds[0], tlst, envp);
}

int	execute_multiple(t_vars *vars)
{
	pid_t	waitpid;
	int		status;

	pipe_next(-1, vars->token_list, vars->environ);
	while (1)
	{
		waitpid = wait(&status);
		if (waitpid == -1)
		{
			if (errno != ECHILD)
				fatal_perror("wait");
			break ;
		}
	}
	return (1);
}
