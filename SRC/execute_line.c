/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_line.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 17:44:20 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/03 13:58:49 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "function.h"

#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

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

static int	nonfatal_error(t_vars vars)
{
	ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
	ft_putendl_fd(vars.token_list->content, STDERR_FILENO);
	return (127);
}

static int	is_pipe_present(t_token *lst)
{
	while (lst)
	{
		if (lst->token == T_PIPE)
		{
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

//TODO: Error handeling
int	execute_single_line(t_vars *vars)
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
			return (vars->exit_code);
		}
		i++;
	}
	if (path_check(vars->token_list->content, find_dir(vars->environ)) != NULL)
		exec_command(vars);
	else if (g_function[i].key == NULL)
		return (nonfatal_error(*vars));
	return (vars->exit_code);
}

//TODO: Error handeling
// TODO: unify
int	execute_line(t_vars *vars)
{
	if (is_pipe_present(vars->token_list))
	{
		return (execute_multiple(vars));
	}
	else
	{
		return (execute_single_line(vars));
	}
}
