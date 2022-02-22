/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_export.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 21:34:06 by xander        #+#    #+#                 */
/*   Updated: 2022/02/22 12:11:23 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

static int	ft_strequel(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '=' && str[len] != '\0')
		len++;
	return (len);
}

int	exec_export(t_vars *vars)
{
	int			i;
	int			err;
	char		*variable;
	char		*content;
	extern char	**environ;

	i = 0;
	err = 0;
	vars->token_list = vars->token_list->next;
	if (vars->token_list == NULL || vars->token_list->token == T_PIPE)
	{
		while (environ[i] != NULL)
		{
			printf("declare -x %s\n", environ[i]);
			i++;
		}
		while (vars->var_list != NULL)
		{
			printf("declare -x %s=%s\n", vars->var_list->variable, vars->var_list->content);
			vars->var_list = vars->var_list->next;
		}
		return (0);
	}
	while (vars->token_list != NULL && vars->token_list->token != T_PIPE)
	{
		content = ft_strchr(vars->token_list->content, '=') + 1;
		variable = ft_substr(vars->token_list->content, 0, ft_strequel(vars->token_list->content));
		new_node(&vars->var_list, variable, content);
		vars->token_list = vars->token_list->next;
	}
	return (0);
}
