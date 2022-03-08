/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_line.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 17:44:20 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/08 18:16:19 by xander        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "function.h"
#include "ft_printf.h"

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

static int	nonfatal_error(t_vars *vars)
{
	ft_dprintf(STDERR_FILENO, "minishell: command not found: %s\n",
		vars->token_list->content);
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
static int	execute_single_cmd(t_vars *vars)
{
	int	i;

	i = 0;
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
		return (nonfatal_error(vars));
	return (vars->exit_code);
}

//TODO: Error handeling
// TODO: unify
int	execute_line(t_vars *vars)
{
	if (is_pipe_present(vars->token_list))
		return (execute_multiple(vars));
	else
		return (execute_single_cmd(vars));
}
