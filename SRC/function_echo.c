/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_echo.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/18 11:55:37 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/22 14:46:12 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/*
	ECHO FUNC:
	Pretty easy. It just prints the line out to STDOUT.
	We only need to use -n as flag, which doesn't place a newline at the end.

	return 0 means I reached the end of the linked list.
	return -1 is an error
	return 1 means otherwise

	LEAK FREE
*/

static int	check_dollar(t_token *temp)
{
	if (ft_strncmp(temp->content, "$", 1) == 0)
		return (true);
	return (false);
}

static int	print_env_variable(t_token *temp)
{
	char	*input_user;
	char	*env;

	input_user = ft_substr(temp->content, 1, \
		ft_strlen(temp->content) - 1);
	env = getenv(input_user);
	if (env == NULL)
		return (-1);
	ft_putstr_fd(env, STDOUT_FILENO);
	return (0);
}

static int	print_echo(t_token *temp, int is_dollar)
{
	int	ret;

	ret = 0;
	if (is_dollar == true)
	{
		ret = print_env_variable(temp);
		return (ret);
	}
	while (temp != NULL)
	{
		if (temp->token != T_LITERAL)
			return (1);
		ft_putstr_fd(temp->content, STDOUT_FILENO);
		if (temp->next != NULL)
			write(STDOUT_FILENO, " ", 1);
		temp = temp->next;
	}
	return (0);
}

int	exec_echo(t_vars *vars)
{
	int		ret;
	int		is_flag;
	int		is_dollar;
	t_token	*temp;

	is_flag = false;
	temp = vars->token_list->next;
	if (temp == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	else if (ft_strcmp(temp->content, "-n") == 0)
	{
		temp = temp->next;
		is_flag = true;
	}
	is_dollar = check_dollar(temp);
	ret = print_echo(temp, is_dollar);
	if (is_flag == false)
		write(STDOUT_FILENO, "\n", 1);
	return (ret);
}
