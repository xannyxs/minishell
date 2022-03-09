/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_command.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:55:19 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/09 13:46:01 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h> /* execve */
#include <stdlib.h> /* exit */
#include <stdio.h> /* perror */

#include <sys/wait.h> /* wait */
#include <sys/types.h>

// TODO: is exit(127) correct?
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
		execve(path, argv, vars->environ);
		perror(*argv);
		exit(127);
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
