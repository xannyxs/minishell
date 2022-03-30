/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   order_export_lst.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/29 15:22:44 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/30 15:28:30 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Prints out the ENV in a sorted way.
*	"`" being the last character */
void	order_sys_env(t_vars vars)
{
	int		i;
	char	c;

	i = 0;
	c = 'A';
	while (vars.environ[i] != NULL)
	{
		if (vars.environ[i][0] == c || vars.environ[i][0] == c + 32)
			print_sys_env(vars, i);
		i++;
		if (c == '`')
			break ;
		else if (vars.environ[i] == NULL)
		{
			i = 0;
			c = c + 1;
		}
	}
}

void	order_usr_env(t_envlist *usr_lst)
{
	char		c;
	t_envlist	*temp;

	c = 'A';
	temp = usr_lst;
	while (temp != NULL)
	{
		if (temp->variable[0] == c || temp->variable[0] == c + 32)
			print_usr_env(temp);
		temp = temp->next;
		if (c == '`')
			break ;
		else if (temp == NULL)
		{
			temp = usr_lst;
			c = c + 1;
		}
	}
}
