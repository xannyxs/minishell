/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_line.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 17:44:20 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/21 21:31:06 by xander        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "function.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

//TODO: Error handeling
int	execute_line(t_vars *vars)
{
	int	i;
	int err;

	i = 0;
	err = 0;
	while (g_function[i].key)
	{
		if (ft_strcmp(vars->token_list->content, g_function[i].key) == 0)
		{
			err = g_function[i].func(vars);
			break ;
		}
		i++;
	}
	if (g_function[i].key == NULL)
	{
		printf("minishell: command not found: %s\n", vars->token_list->content);
		return (127);
	}
	return (0);
}
