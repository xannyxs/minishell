/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_env.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 22:18:38 by xander        #+#    #+#                 */
/*   Updated: 2022/03/09 14:40:55 by xander        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

int	exec_env(char *argv[], t_vars *vars)
{
	int	i;

	i = 0;
	argv = NULL;
	vars->exit_code = 0;
	while (vars->environ[i] != NULL)
	{
		printf("%s\n", vars->environ[i]);
		i++;
	}
	return (0);
}
