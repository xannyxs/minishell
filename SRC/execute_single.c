/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_single.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:55:19 by xvoorvaa      #+#    #+#                 */
<<<<<<< HEAD:SRC/exec_command.c
/*   Updated: 2022/03/09 14:40:55 by xander        ########   odam.nl         */
=======
/*   Updated: 2022/03/09 16:49:00 by jobvan-d      ########   odam.nl         */
>>>>>>> master:SRC/execute_single.c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h> /* execve */
#include <stdlib.h> /* exit */
#include <stdio.h> /* perror */

#include <sys/wait.h> /* wait */
#include <sys/types.h>

<<<<<<< HEAD:SRC/exec_command.c
// TODO: is exit(127) correct?
int	exec_command(char *argv[], t_vars *vars)
=======
int	exec_command(char **argv, t_vars *vars)
>>>>>>> master:SRC/execute_single.c
{
	pid_t	pid;
	char	*path;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		path = pathresolve_tryfind(*argv, vars->environ);
		if (!path)
			path = "";
		if (execve(path, argv, vars->environ) == -1)
		{
			perror(*argv);
			exit(126 + (errno == 2));
		}
	}
	else if (pid == -1)
		fatal_perror("fork");
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		vars->exit_code = WEXITSTATUS(status);
	}
	return (vars->exit_code);
}
