/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_echo.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/18 11:55:37 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/18 12:20:22 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <stdbool.h>

static int	print_echo(t_vars vars, int flag)
{
	while (vars.token_list != NULL)
	{
		if (vars.token_list->token != T_LITERAL)
		{
			if (flag == false)
				write(STDOUT_FILENO, "\n", 1);
			return (1);
		}
		ft_putstr_fd(vars.token_list->content, STDOUT_FILENO);
		if (vars.token_list->next != NULL)
			write(STDOUT_FILENO, " ", 1);
		vars.token_list = vars.token_list->next;
	}
	return (0);
}

int	exec_echo(t_vars vars)
{
	int	ret;
	int	flag;

	flag = false;
	vars.token_list = vars.token_list->next;
	if (vars.token_list == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	else if (ft_strcmp(vars.token_list->content, "-n") == 0)
	{
		vars.token_list = vars.token_list->next;
		flag = true;
	}
	ret = print_echo(vars, flag);
	if (flag == false)
		write(STDOUT_FILENO, "\n", 1);
	return (ret);
}
