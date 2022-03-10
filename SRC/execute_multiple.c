/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_multiple.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/10 10:50:28 by xander        #+#    #+#                 */
/*   Updated: 2022/03/10 22:28:02 by jobvan-d      ########   odam.nl         */
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
		exit(126 + (errno == 2));
	}
}

// TODO: builtins
// TODO: redir
// TODO: perhaps create_argv in m_proc?
// TODO: pipe reordering, perhaps with m_close which doesn't
// 		do anything when -1
// TODO: > yolo | cat
/* runs the next command in the pipe list. Returns the pid of the final
 * command executed. */
pid_t	pipe_next(int readfd, t_token *tlst, t_vars *vars)
{
	int		pfds[2];
	char	**argv;
	int		outfdchanged;
	pid_t	pid;

	if (pipe(pfds) == -1)
		fatal_perror("pipe");
	outfdchanged = 0;
	argv = create_argv_advanced(&tlst, &readfd, &pfds[1], &outfdchanged);
	if (tlst == NULL && !outfdchanged)
	{
		close(pfds[1]);
		pfds[1] = -1;
	}
	/*if (outfdchanged)
	{
		close(pfds[0]);
		pfds[0] = -1;
	}*/
	pid = fork();
	if (pid == -1)
		fatal_perror("fork");
	else if (pid == 0)
	{
		ft_close_fd(pfds[0]);
		m_proc(readfd, pfds[1], argv, vars);
	}
	free(argv);
	ft_close_fd(readfd);
	ft_close_fd(pfds[1]);
	if (tlst == NULL)
	{
		ft_close_fd(pfds[0]);
		return (pid);
	}
	return (pipe_next(pfds[0], tlst, vars));
}

// TODO: signal error returns
// TODO: cat | ls
int	execute_multiple(t_vars *vars)
{
	pid_t	waitpid;
	pid_t	final_pid;
	int		status;

	final_pid = pipe_next(-1, vars->token_list, vars);
	while (1)
	{
		waitpid = wait(&status);
		if (waitpid == -1)
		{
			if (errno != ECHILD)
				fatal_perror("wait");
			break ;
		}
		else if (WIFEXITED(status) && waitpid == final_pid)
		{
			vars->exit_code = WEXITSTATUS(status);
		}
	}
	return (vars->exit_code);
}
