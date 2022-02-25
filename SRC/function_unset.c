/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_unset.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 16:48:33 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/25 13:53:54 by jobvan-d      ########   odam.nl         */
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

static int	move_arrays(t_vars *vars, t_token *temp)
{
	int		i;
	char	*temp_var;

	i = 0;
	temp_var = ft_strjoin(temp->content, "=");
	while (vars->environ[i] != NULL)
	{
		if (ft_strncmp(temp_var, vars->environ[i], \
				ft_strlen(temp_var)) == 0)
		{
			while (vars->environ[i + 1] != NULL)
			{
				free(vars->environ[i]);
				vars->environ[i] = ft_strdup(vars->environ[i + 1]);
				i++;
			}
			free(vars->environ[i]);
			vars->environ[i] = NULL;
			return (1);
		}
		i++;
	}
	free(temp_var);
	return (0);
}

int	exec_unset(t_vars *vars)
{
	t_token	*temp;

	if (vars->token_list->next == NULL)
		return (0);
	temp = vars->token_list->next;
	move_arrays(vars, temp);
	return (0);
}
