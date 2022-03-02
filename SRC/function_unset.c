/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_unset.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 16:48:33 by xvoorvaa      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2022/02/24 14:21:56 by xvoorvaa      ########   odam.nl         */
=======
/*   Updated: 2022/02/25 13:53:54 by jobvan-d      ########   odam.nl         */
>>>>>>> origin/master
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
<<<<<<< HEAD
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
=======
>>>>>>> origin/master
	int		i;
	char	*temp_var;

	i = 0;
	temp_var = ft_strjoin(temp->content, "=");
	if (temp_var == NULL)
		fatal_error("malloc:");
	while (vars->environ[i] != NULL)
	{
		if (ft_strncmp(temp_var, vars->environ[i], \
				ft_strlen(temp_var)) == 0)
		{
			while (vars->environ[i + 1] != NULL)
			{
				free(vars->environ[i]);
<<<<<<< HEAD
				vars->environ[i] = NULL;
				return (0);
=======
				vars->environ[i] = ft_strdup(vars->environ[i + 1]);
				i++;
>>>>>>> origin/master
			}
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
<<<<<<< HEAD
	temp  = vars->token_list->next;
	ret = check_env_vars(vars, temp);
	if (ret != 0)
		check_usr_vars(vars, temp);
=======
	temp = vars->token_list->next;
	move_arrays(vars, temp);
>>>>>>> origin/master
	return (0);
}
