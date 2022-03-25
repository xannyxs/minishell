/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_single.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:55:19 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/25 21:01:40 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <unistd.h> /* execve */
#include <stdlib.h> /* exit */
#include <stdio.h> /* perror */

#include <sys/wait.h> /* wait */
#include <sys/types.h>
#include <stdbool.h>

/*
	The ft_split in this function is for the function export.
	See function_export.c for more info.
*/
int	exec_command(char **argv, t_vars *vars)
{
	int		status;
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == 0)
	{
		signals_child();
		if (ft_strchr(argv[0], ' ') != NULL)
		{
			argv = ft_split(argv[0], ' ');
			if (argv == NULL)
				malloc_fail();
		}
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
	deactivate_signals();
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) == true)
		vars->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status) == true)
		vars->exit_code = WTERMSIG(status) + 128;
	signals();
	return (vars->exit_code);
}
