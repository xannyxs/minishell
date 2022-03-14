/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_env.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 22:18:38 by xander        #+#    #+#                 */
/*   Updated: 2022/03/14 18:53:55 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <unistd.h>
#include <stdio.h>

int	exec_env(char *argv[], t_vars *vars)
{
	int			i;
	t_envlist	*temp;

	i = 0;
	argv = NULL;
	temp = vars->var_list;
	vars->exit_code = 0;
	while (vars->environ[i] != NULL)
	{
		ft_putstr_fd(vars->environ[i], STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	while (temp != NULL)
	{
		if (temp->content != NULL)
			printf("%s=%s\n", temp->variable, temp->content);
		temp = temp->next;
	}
	return (0);
}
