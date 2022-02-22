/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_exit.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 11:06:19 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/22 14:38:18 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
	FUNCTION EXIT:
	Pretty easy: You type in "exit" and it will exit the shell.
	You can put a number after the exit and
	it will signal the exit status for the next time.

	LEAK FREE
*/

int	exec_exit(t_vars *vars)
{
	int	i;
	t_token	*temp;

	i = 0;
	temp = vars->token_list;
	if (vars->token_list->next != NULL)
		temp = temp->next;
	if (ft_strcmp(temp->content, "exit") == 0)
		exit (0);
	while (ft_isdigit(temp->content[i]) == true)
		i++;
	if (ft_isdigit(temp->content[i]) == false && \
		temp->content[i] != '\0')
	{
		printf("bash: exit: %s: numeric argument required\n", temp->content);
		exit (255);
	}
	vars->err_output = ft_atoi(temp->content);
	exit(vars->err_output);
}
