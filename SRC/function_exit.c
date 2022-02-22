/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_exit.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 11:06:19 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/22 11:34:09 by xvoorvaa      ########   odam.nl         */
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

	i = 0;
	if (vars->token_list->next != NULL)
		vars->token_list = vars->token_list->next;
	if (ft_strcmp(vars->token_list->content, "exit") == 0)
		exit (0);
	while (ft_isdigit(vars->token_list->content[i]) == true)
		i++;
	if (ft_isdigit(vars->token_list->content[i]) == false && \
		vars->token_list->content[i] != '\0')
	{
		printf("bash: exit: %s: numeric argument required\n", vars->token_list->content);
		exit (255);
	}
	vars->err_output = ft_atoi(vars->token_list->content);
	exit(vars->err_output);
}
