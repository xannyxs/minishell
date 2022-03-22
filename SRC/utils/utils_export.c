/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_export.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/14 17:04:33 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/22 14:51:42 by jobvan-d      ########   odam.nl         */
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
		malloc_fail();
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
	int	i;

	i = 0;
	while (vars.environ[i] != NULL)
	{
		if (ft_strncmp(vars.environ[i], variable, ft_strlen(variable)) == 0)
			return (true);
		i++;
	}
	while (vars.var_list != NULL)
	{
		if (ft_strcmp(vars.var_list->variable, variable) == 0)
			return (true);
		vars.var_list = vars.var_list->next;
	}
	return (false);
}

static void	replace_sys_env(char **environ, char *variable, char *content)
{
	char	*temp;

	free(*environ);
	temp = ft_strjoin(variable, "=");
	if (temp == NULL)
		malloc_fail();
	*environ = ft_strjoin(temp, content);
	if (*environ == NULL)
		malloc_fail();
	free(temp);
	free(content);
}

void	replace_dup_env(t_vars *vars, char *variable, char *content)
{
	int			i;
	t_envlist	*temp;

	i = 0;
	temp = vars->var_list;
	while (vars->environ[i] != NULL)
	{
		if (ft_strncmp(vars->environ[i], variable, ft_strlen(variable)) == 0)
			replace_sys_env(&vars->environ[i], variable, content);
		i++;
	}
	while (temp != NULL)
	{
		if (ft_strcmp(temp->variable, variable) == 0)
		{
			free(temp->content);
			temp->content = content;
			return ;
		}
		temp = temp->next;
	}
}
