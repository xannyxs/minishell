/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/09 12:42:49 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/31 16:13:05 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "function.h"
#include "libft.h" /* ft_strcmp */
#include "ft_printf.h"

#include <unistd.h> /* close, execve, dup etc. */
#include <stdlib.h> /* exit */
#include <string.h> /* strerror */

#include <sys/errno.h>
#include <sys/stat.h> /* stat */

/* returns a t_function entry if it's found, struct filled with zeroes
 * when not. */
t_function	get_function(const char *name)
{
	const t_function	funcs[] = {
	{"echo", &exec_echo, 1},
	{"cd", &exec_cd, 0},
	{"pwd", &exec_pwd, 1},
	{"export", &exec_export, 0},
	{"unset", &exec_unset, 0},
	{"env", &exec_env, 1},
	{"exit", &exec_exit, 0},
	{0, NULL, 0}
	};
	int					i;

	i = 0;
	while (funcs[i].key != NULL)
	{
		if (ft_strcmp(funcs[i].key, name) == 0)
		{
			return (funcs[i]);
		}
		i++;
	}
	return (funcs[i]);
}

/* runs a builtin if it encounters it, exits after with the correct exit code.
 * this is to be used in forks. */
static void	run_builtin(char **args, t_vars *vars)
{
	t_function	tf;

	tf = get_function(*args);
	if (tf.key != NULL)
	{
		exit((*tf.func)(args, vars));
	}
}

/* closes a file descriptor if it's not -1 */
void	ft_close_fd(const int fd)
{
	if (fd != -1)
	{
		close(fd);
	}
}

static void	fancy_error(const char *path, const char *cmd_name)
{
	struct stat	path_stat;
	char		*msg;
	int			exit_code;

	msg = NULL;
	exit_code = 126;
	if (errno == EACCES)
	{
		stat(path, &path_stat);
		if (S_ISDIR(path_stat.st_mode))
		{
			msg = "is a directory";
		}
	}
	else if (errno == ENOENT)
	{
		msg = "command not found";
		exit_code++;
	}
	if (!msg)
		msg = strerror(errno);
	ft_dprintf(2, "minishell: %s: %s\n", cmd_name, msg);
	exit(exit_code);
}

void	m_proc(int infd, int outfd, char **args, t_vars *vars)
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
	run_builtin(args, vars);
	path = pathresolve_tryfind(*args, vars->environ);
	if (!path)
		path = "";
	if (execve(path, args, vars->environ) == -1)
	{
		fancy_error(path, *args);
	}
}
