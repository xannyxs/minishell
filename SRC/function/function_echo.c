/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_echo.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/18 11:55:37 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/09 12:47:18 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdbool.h>
#include <unistd.h> /* STDOUT_FILENO */

/*
	ECHO FUNC:
	Pretty easy. It just prints the line out to STDOUT.
	We only need to use -n as flag, which doesn't place a newline at the end.

	return 0 means I reached the end of the linked list.
	return -1 is an error
	return 1 means otherwise

	LEAK FREE
*/

static int	print_echo(t_token *temp)
{
	while (temp != NULL)
	{
		if (temp->token != T_LITERAL)
			return (1);
		ft_putstr_fd(temp->content, STDOUT_FILENO);
		if (temp->next != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		temp = temp->next;
	}
	return (0);
}

int	exec_echo(char **argv, t_vars *vars)
{
	int		ret;
	int		is_flag;
	t_token	*temp;

	is_flag = false;
	temp = vars->token_list->next;
	if (temp == NULL)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	else if (ft_strcmp(temp->content, "-n") == 0)
	{
		temp = temp->next;
		is_flag = true;
	}
	ret = print_echo(temp);
	if (is_flag == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (ret);
}
