/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_exit.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 11:06:19 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/04/05 14:41:39 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* ft_isdigit */
#include "ft_printf.h" /* ft_dprintf */

#include <stdlib.h> /* Exit */
#include <unistd.h> /* STD */

static void	write_num_error(const char *arg)
{
	ft_dprintf(STDERR_FILENO,
		"minishell: exit: %s: numeric argument required\n", arg);
	exit(255);
}

static void	check_valid_chars(const char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '-')
		i++;
	while (ft_isdigit(arg[i]) == true)
		i++;
	if (ft_isdigit(arg[i]) == false && arg[i] != '\0')
		write_num_error(arg);
}

/*
	FUNCTION EXIT:
	You type in "exit" and it will exit the shell.
	You can put a number after the exit.
	It will output the exit status
*/
int	exec_exit(char *argv[], t_vars *vars)
{
	ft_dprintf(STDERR_FILENO, "exit\n");
	if (argv[1] == NULL)
		exit(vars->exit_code);
	check_valid_chars(argv[1]);
	if (argv[2] != NULL)
	{
		vars->exit_code = ERROR;
		ft_dprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
	}
	else
	{
		vars->exit_code = ft_atoi(argv[1]);
		exit(vars->exit_code);
	}
	return (vars->exit_code);
}
