/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_unset.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 16:48:33 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/21 20:59:21 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdio.h>
#include <stdlib.h>

/*
	UNSET:
	Unsets an env variable or usr variable.

	Moet ook envlist checken voor $-sign
	Keys are unique and needs to be overwriten
	SEGFAULT usr_vars
*/

static int	check_usr_vars(char *argv[], t_vars *vars)
{
	t_envlist	*prev;
	t_envlist	*temp_env;

	prev = NULL;
	temp_env = vars->var_list;
	if (temp_env != NULL && ft_strcmp(temp_env->variable, argv[1]) == 0)
	{
		vars->var_list = temp_env->next;
		free(temp_env->variable);
		free(temp_env->content);
		free(temp_env);
		return (0);
	}
	while (temp_env != NULL && ft_strcmp(temp_env->variable, argv[1]) != 0)
	{
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

static int	check_env_vars(char *argv[], t_vars *vars)
{
	int		i;
	char	*temp_var;

	i = 0;
	temp_var = ft_strjoin(argv[1], "=");
	while (vars->environ[i] != NULL)
	{
		if (temp_var == NULL)
			fatal_perror("malloc:");
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
			vars->environ[i] = NULL;
			return (0);
		}
		i++;
	}
	free(temp_var);
	return (-1);
}

int	exec_unset(char *argv[], t_vars *vars)
{
	int		ret;

	if (argv[1] == NULL)
		return (0);
	ret = check_env_vars(argv, vars);
	if (ret != 0)
		check_usr_vars(argv, vars);
	return (0);
}
