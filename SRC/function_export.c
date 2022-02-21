/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_export.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 21:34:06 by xander        #+#    #+#                 */
/*   Updated: 2022/02/21 22:57:13 by xander        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

int	exec_export(t_vars *vars)
{
	int			i;
	int			err;
	//char		*variable;
	extern char	**environ;

	i = 0;
	err = 0;
	vars->var_list = NULL;
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
	}
	//while (vars->token_list != NULL || vars->token_list->token != T_PIPE)
	//{
	//	variable = ft_strchr(vars->token_list->content, '=');
	//	vars->token_list = vars->token_list->next;
	//}
	return (0);
}
