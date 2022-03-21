/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_exit.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 11:06:19 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/21 16:35:58 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"

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

static void	write_num_error(const char *arg)
{
	ft_dprintf(STDERR_FILENO,
		"minishell: exit: %s: numeric argument required\n", arg);
	exit(255);
}

int	exec_exit(char *argv[], t_vars *vars)
{
	int	i;

	i = 0;
	if (argv[1] == NULL)
		exit(vars->exit_code);
	while (ft_isdigit(argv[1][i]) == true)
		i++;
	if (ft_isdigit(argv[1][i]) == false && argv[1][i] != '\0')
		write_num_error(argv[1]);
	if (argv[2] != NULL)
	{
		vars->exit_code = 1;
		ft_dprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
	}
	else
	{
		vars->exit_code = ft_atoi(argv[1]);
		ft_dprintf(STDERR_FILENO, "exit\n");
		exit(vars->exit_code);
	}
}
