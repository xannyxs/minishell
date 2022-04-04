/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_multiple.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/10 10:50:28 by xander        #+#    #+#                 */
/*   Updated: 2022/04/04 17:59:46 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "function.h"

#include <unistd.h> /* execve, dup, close etc. */
#include <stdlib.h> /* malloc */
#include <sys/wait.h> /* wait */

static pid_t	pn_fork(int readfd, int *pfds, char **argv, t_vars *vars)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		fatal_perror("fork");
	else if (pid == 0)
	{
		signals_pipe();
		close(pfds[0]);
		m_proc(readfd, pfds[1], argv, vars);
	}
	return (pid);
}

/* damn you norm! */
static void	pn_cleanup(int readfd, int *pfds, char **argv)
{
	free(argv);
	ft_close_fd(readfd);
	ft_close_fd(pfds[1]);
}

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
	if (pstatus < 0 || (tlst == NULL && !(pstatus & M_PS_REDIRECTED_STDOUT)))
	{
		close(pfds[1]);
		pfds[1] = -1;
	}
	if (pstatus >= 0)
		pid = pn_fork(readfd, pfds, argv, vars);
	pn_cleanup(readfd, pfds, argv);
	if (tlst == NULL || (pstatus & M_PS_HEREDOC_SIGINT))
	{
		if (pstatus & M_PS_HEREDOC_SIGINT)
			vars->exit_code = ERROR;
		close(pfds[0]);
		return (pid);
	}
	return (pipe_next(pfds[0], tlst, vars));
}

static void	wait_for_childs(const pid_t final_pid, t_vars *vars)
{
	pid_t	waitchild;
	int		status;

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
}

int	execute_multiple(t_vars *vars)
{
	pid_t	final_pid;

	deactivate_signals_pipes();
	final_pid = pipe_next(-1, vars->token_list, vars);
	if (errno != 0)
		vars->exit_code = errno;
	wait_for_childs(final_pid, vars);
	signals_default();
	return (vars->exit_code);
}
