/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_export.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/14 17:04:33 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/14 17:07:19 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdbool.h>
#include <stdlib.h>

int	check_dup_env(t_vars vars, char *variable)
{
	while (vars.var_list != NULL)
	{
		if (ft_strcmp(vars.var_list->variable, variable) == 0)
			return (true);
		vars.var_list = vars.var_list->next;
	}
	return (false);
}

void	replace_dup_env(t_vars *vars, char *variable, char *content)
{
	t_envlist	*temp;

	temp = vars->var_list;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->variable, variable) == 0)
		{
			free(temp->content);
			temp->content = content;
		}
		temp = temp->next;
	}
}
