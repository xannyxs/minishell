/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_line.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 17:44:20 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/17 18:15:38 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdbool.h>

/*
	ECHO FUNC:
	Pretty easy. It just prints the line out to STDOUT.
	We only need to use -n as flag, which doesn't place a newline.
*/

static int	exec_echo(t_parsing parsing)
{
	int	flag;

	flag = false;
	parsing.token_list = parsing.token_list->next;
	if (parsing.token_list == NULL)
		printf("\n");
	else if (ft_strcmp(parsing.token_list->content, "-n") == 0)
	{
		parsing.token_list = parsing.token_list->next;
		flag = true;
	}
	while (parsing.token_list != NULL)
	{
		if (parsing.token_list->token != T_LITERAL)
		{
			if (flag == false)
				printf("\n");
			return (1);
		}
		printf("%s ", parsing.token_list->content);
		parsing.token_list = parsing.token_list->next;
	}
	if (flag == false)
		printf("\n");
	return (0);
}

void	execute_line(t_parsing parsing)
{
	int	i;

	i = 0;
	if (ft_strcmp(parsing.prompt[i], "echo") == 0)
		exec_echo(parsing);
}
