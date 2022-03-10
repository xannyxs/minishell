/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_multiple.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 16:31:14 by jobvan-d      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2022/03/09 14:49:14 by xander        ########   odam.nl         */
=======
/*   Updated: 2022/03/09 16:45:20 by jobvan-d      ########   odam.nl         */
>>>>>>> master
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

// I hate this duplicate code
<<<<<<< HEAD
static void	final_proc(int readfd, char *argv[], t_vars *vars,
=======
static pid_t	final_proc(int readfd, char **argv, t_vars *vars,
>>>>>>> master
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
	return (pid);
}

// TODO: builtins
// TODO: redir
// TODO: perhaps create_argv in m_proc?
/* runs the next command in the pipe list. Returns the pid of the final
 * command executed. */
pid_t	pipe_next(int readfd, t_token *tlst, t_vars *vars)
{
	int		pfds[2];
	char	**argv;
	pid_t	pid;
	t_token	*old_tlst;

	old_tlst = tlst;
	argv = create_argv(&tlst);
	if (tlst == NULL)
	{
		return (final_proc(readfd, argv, vars, old_tlst));
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
