/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_exit.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 11:06:19 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/07 14:49:54 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

/*
	FUNCTION EXIT:
	Pretty easy: You type in "exit" and it will exit the shell.
	You can put a number after the exit and
	it will signal the exit status for the next time.

	LEAK FREE
*/

static void	write_error(t_token *temp)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(temp->content, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	exit(255);
}

int	exec_exit(t_vars *vars)
{
	int		i;
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
		write_error(temp);
	vars->exit_code = ft_atoi(temp->content);
	exit(vars->exit_code);
}
