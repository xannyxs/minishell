/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_unset.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 16:48:33 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/07 12:48:12 by xander        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdio.h>
#include <stdlib.h>

/*
	UNSET:
	Unsets a env variable.

	This function doesn't remove $
*/

static int	check_usr_vars(t_vars *vars, t_token *temp)
{
	t_envlist *temp_env = vars->var_list, *prev;

	if (temp_env != NULL && ft_strcmp(temp_env->variable, temp->content) == 0)
	{
		vars->var_list = temp_env->next;
		free(temp_env->variable);
		free(temp_env->content);
		free(temp_env);
		return (0);
	}
	while (temp_env != NULL && ft_strcmp(temp_env->variable, temp->content) == 0)
	{
		print_list(vars->var_list);
		prev = temp_env;
		temp_env = temp_env->next;
	}
	if (temp_env == NULL)
		return (-1);
	prev->next = temp_env->next;
	free(temp_env->variable);
	free(temp_env->content);
	free(temp_env);
	return (0);
}

static int	check_env_vars(t_vars *vars, t_token *temp)
{
	int		i;
	char	*temp_var;

	i = 0;
	temp_var = ft_strjoin(temp->content, "=");
	if (temp_var == NULL)
		fatal_perror("malloc:");
	while (vars->environ[i] != NULL)
	{
		if (ft_strncmp(temp_var, vars->environ[i], \
				ft_strlen(temp_var)) == 0)
		{
			free(vars->environ[i]);
			while (vars->environ[i + 1] != NULL)
			{
				vars->environ[i] = vars->environ[i + 1];
				i++;
			}
			free(temp_var);
			free(vars->environ[i]);
			vars->environ[i] = NULL;
			return (1);
		}
		i++;
	}
	free(temp_var);
	return (-1);
}

int	exec_unset(t_vars *vars)
{
	int		ret;
	t_token	*temp;

	if (vars->token_list->next == NULL)
		return (0);
	temp  = vars->token_list->next;
	ret = check_env_vars(vars, temp);
	if (ret != 0)
		check_usr_vars(vars, temp);
	return (0);
}
