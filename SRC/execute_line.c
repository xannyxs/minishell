/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_line.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 17:44:20 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/23 13:00:19 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "function.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

static const t_function	g_function[] = {
{"echo", &exec_echo},
{"cd", &exec_cd},
{"pwd", &exec_pwd},
{"export", &exec_export},
{"unset", &exec_unset},
{"env", &exec_env},
{"exit", &exec_exit},
{0, NULL}
};

//TODO: Error handeling
int	execute_line(t_vars *vars)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (g_function[i].key)
	{
		if (ft_strcmp(vars->token_list->content, g_function[i].key) == 0)
		{
			vars->exit_code = g_function[i].func(vars);
			break ;
		}
		i++;
	}
	if (g_function[i].key == NULL)
	{
		printf("minishell: command not found: %s\n", vars->token_list->content);
		return (127);
	}
	return (vars->exit_code);
}
