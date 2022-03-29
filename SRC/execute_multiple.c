/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_multiple.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/10 10:50:28 by xander        #+#    #+#                 */
/*   Updated: 2022/03/29 16:02:32 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "function.h"

#include <unistd.h> /* execve, dup, close etc. */
#include <stdlib.h> /* malloc */
#include <sys/wait.h> /* wait */
#include <stdio.h> /* perror */

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
		close(infd);
	}
	if (outfd != -1)
	{
		close(STDOUT_FILENO);
		if (dup(outfd) == -1)
			fatal_perror("dup(outfd)");
		close(outfd);
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

// TODO: norm
/* runs the next command in the pipe list. Returns the pid of the final
 * command executed. */
pid_t	pipe_next(int readfd, t_token *tlst, t_vars *vars)
{
	int		pfds[2];
	char	**argv;
	int		pstatus;
	pid_t	pid;

	if (pipe(pfds) == -1)
		fatal_perror("pipe");
	argv = create_argv_advanced(&tlst, &readfd, &pfds[1], &pstatus);
	if (pstatus & M_PS_HEREDOC_SIGINT)
		vars->exit_code = ERROR;
	if (pstatus < 0 || (tlst == NULL && !(pstatus & M_PS_REDIRECTED_STDOUT)))
	{
		close(pfds[1]);
		pfds[1] = -1;
	}
	if (pstatus >= 0)
	{
		pid = fork();
		if (pid == -1)
			fatal_perror("fork");
		else if (pid == 0)
		{
			signals_pipe();
			close(pfds[0]);
			m_proc(readfd, pfds[1], argv, vars);
		}
	}
	free(argv);
	ft_close_fd(readfd);
	ft_close_fd(pfds[1]);
	if (tlst == NULL)
	{
		close(pfds[0]);
		return (pid);
	}
	return (pipe_next(pfds[0], tlst, vars));
}

int	execute_multiple(t_vars *vars)
{
	pid_t	waitchild;
	pid_t	final_pid;
	int		status;

	deactivate_signals_pipes();
	final_pid = pipe_next(-1, vars->token_list, vars);
	if (errno != 0)
		vars->exit_code = errno;
	while (true)
	{
		waitchild = wait(&status);
		if (waitchild == -1)
		{
			if (errno != ECHILD)
				fatal_perror("wait");
			break ;
		}
		if (final_pid == waitchild)
		{
			if (WIFEXITED(status) == true)
				vars->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status) == true)
				vars->exit_code = WTERMSIG(status) + 128;
		}
	}
	signals_default();
	return (vars->exit_code);
}
