/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_echo.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/18 11:55:37 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/21 21:15:04 by xander        ########   odam.nl         */
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
*/

static int	check_dollar(t_vars vars)
{
	if (ft_strncmp(vars.token_list->content, "$", 1) == 0)
		return (true);
	return (false);
}

static int	print_env_variable(t_vars vars)
{
	char	*input_user;
	char	*env;

	input_user = ft_substr(vars.token_list->content, 1, \
		ft_strlen(vars.token_list->content) - 1);
	env = getenv(input_user);
	if (env == NULL)
		return (-1);
	ft_putstr_fd(env, STDOUT_FILENO);
	return (0);
}

static int	print_echo(t_vars vars, int is_dollar)
{
	int	ret;

	ret = 0;
	if (is_dollar == true)
	{
		ret = print_env_variable(vars);
		return (ret);
	}
	while (vars.token_list != NULL)
	{
		if (vars.token_list->token != T_LITERAL)
			return (1);
		ft_putstr_fd(vars.token_list->content, STDOUT_FILENO);
		if (vars.token_list->next != NULL)
			write(STDOUT_FILENO, " ", 1);
		vars.token_list = vars.token_list->next;
	}
	return (0);
}

int	exec_echo(t_vars *vars)
{
	int	ret;
	int	is_flag;
	int	is_dollar;

	is_flag = false;
	vars->token_list = vars->token_list->next;
	if (vars->token_list == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	else if (ft_strcmp(vars->token_list->content, "-n") == 0)
	{
		vars->token_list = vars->token_list->next;
		is_flag = true;
	}
	is_dollar = check_dollar(*vars);
	ret = print_echo(*vars, is_dollar);
	if (is_flag == false)
		write(STDOUT_FILENO, "\n", 1);
	return (ret);
}
