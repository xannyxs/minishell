/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_line.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 17:44:20 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/18 11:53:35 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

/*
	ECHO FUNC:
	Pretty easy. It just prints the line out to STDOUT.
	We only need to use -n as flag, which doesn't place a newline at the end.
*/

static int	exec_echo(t_vars vars)
{
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
	if (flag == false)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

void	execute_line(t_vars vars)
{
	int	i;

	i = 0;
	if (ft_strcmp(vars.prompt[i], "echo") == 0)
		exec_echo(vars);
}
