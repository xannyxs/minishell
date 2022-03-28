/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_echo.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/18 11:55:37 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/28 19:20:04 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdbool.h> /* TRUE OR FALSE */
#include <stdio.h>
#include <unistd.h> /* STDOUT_FILENO */
#include <stdlib.h>

/*
	ECHO FUNC:
	Pretty easy. It just prints the line out to STDOUT.
	We only need to use -n as flag, which doesn't place a newline at the end.

	LEAK FREE
*/

static int	skip_flags(char *argv[], int i)
{
	int	j;

	j = 1;
	while (argv[i] != NULL)
	{
		if (argv[i][0] == '-')
		{
			while (argv[i][j] == 'n' && argv[i][j] != '\0')
				j++;
			if (argv[i][j] != 'n' && argv[i][j] != '\0')
				return (i);
			else if (argv[i][j] == '\0')
			{
				j = 1;
				i++;
			}
		}
		else
			return (i);
	}
	return (i);
}

static int	ft_isquoted(char *argv[])
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (argv[i] != NULL)
	{
		if (ft_strncmp(argv[i], "-n", 2) == 0)
		{
			while (argv[i][j] == 'n')
			{
				j++;
				if (argv[i][j] == '\0')
					return (false);
			}
		}
		i++;
	}
	return (true);
}

static void	print_echo(int i, char *argv[])
{
	while (argv[i] != NULL)
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		i++;
		if (argv[i] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
}

int	exec_echo(char *argv[], t_vars *vars)
{
	int	i;
	int	is_flag;

	i = 1;
	is_flag = false;
	vars->exit_code = 0;
	if (argv[1] == NULL)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (vars->exit_code);
	}
	else if (ft_strncmp(argv[1], "-n", 2) == 0)
	{
		i = skip_flags(argv, i);
		if (ft_isquoted(argv) == false)
			is_flag = true;
	}
	print_echo(i, argv);
	if (is_flag == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (vars->exit_code);
}
