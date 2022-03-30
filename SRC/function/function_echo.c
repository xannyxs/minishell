/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_echo.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/18 11:55:37 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/30 14:47:54 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* strcmp */

#include <unistd.h> /* STDOUT_FILENO */

/*
	ECHO FUNC:
	Pretty easy. It just prints the line out to STDOUT.
	We only need to use -n as flag, which doesn't place a newline at the end.

	LEAK FREE
*/

static bool	is_valid_n_flag(const char *arg)
{
	if (*arg == '-')
	{
		arg++;
		if (*arg != 'n')
			return (false);
		while (*arg == 'n')
		{
			arg++;
		}
		return (*arg == '\0');
	}
	return (false);
}

static int	skip_n_flags(char *argv[], int i)
{
	while (argv[i] != NULL)
	{
		if (is_valid_n_flag(argv[i]))
		{
			i++;
		}
		else
			break ;
	}
	return (i);
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

	i = 1;
	vars->exit_code = 0;
	if (argv[1] == NULL)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (vars->exit_code);
	}
	i = skip_n_flags(argv, i);
	print_echo(i, argv);
	if (i == 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (vars->exit_code);
}
