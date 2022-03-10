/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_single.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/10 10:51:18 by xander        #+#    #+#                 */
/*   Updated: 2022/03/10 10:51:20 by xander        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h> /* execve */
#include <stdlib.h> /* exit */
#include <stdio.h> /* perror */

#include <sys/wait.h> /* wait */
#include <sys/types.h>

int	exec_command(char **argv, t_vars *vars)
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
