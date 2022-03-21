/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_export.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/14 17:04:33 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/21 20:06:44 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void	print_sys_env(t_vars vars, int i)
{
	char	**split_env;

	split_env = ft_split(vars.environ[i], '=');
	if (split_env == NULL)
		fatal_perror("malloc");
	if (split_env[1] == NULL)
		printf("declare -x %s=\"\"\n", split_env[0]);
	else
		printf("declare -x %s=\"%s\"\n", split_env[0], split_env[1]);
	ft_free_str_arr(split_env);
}

void	print_usr_env(t_envlist *temp)
{
	if (temp->content != NULL)
		printf("declare -x %s=\"%s\"\n", temp->variable, temp->content);
	else if (temp->content == NULL)
		printf("declare -x %s\n", temp->variable);
	else
		printf("declare -x %s=\"\"\n", temp->variable);
}

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
