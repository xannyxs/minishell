/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_multiple.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 16:31:14 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/09 13:48:21 by jobvan-d      ########   odam.nl         */
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

/* runs a builtin if it encounters it. */
static void	m_run_builtin(char **args, t_vars *vars)
{
	t_function	tf;

	tf = get_function(*args);
	if (tf.key != NULL)
	{
		exit((*tf.func)(args, vars));
	}
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
