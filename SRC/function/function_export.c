/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_export.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 21:34:06 by xander        #+#    #+#                 */
/*   Updated: 2022/03/14 15:31:33 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

/*
	export hoi
	export hoi=

	Moet ook envlist checken voor $-sign
	Keys are unique and needs to be overwriten
*/

/*
	First check is the first char being checked
	if it is an underscore or a character in the alphabet

	Second check is alphabet, underscore and numbers
*/
static int	check_chars(char *argv[], t_vars *vars, int i)
{
	int	j;

	j = 0;
	if (!(ft_isalpha(argv[i][0]) == true || argv[i][0] == '_'))
	{
		ft_dprintf(STDERR_FILENO, \
		"minishell: export: '%s': not a valid identifier\n", argv[i]);
		vars->exit_code = 1;
		return (-1);
	}
	while (ft_isalpha(argv[i][j]) == true || ft_isdigit(argv[i][j] == true || \
		argv[i][j] == '_'))
	{
		j++;
		if (!(ft_isalpha(argv[i][j]) == true || \
			ft_isdigit(argv[i][j] == true || \
			argv[i][j] == '_') || argv[i][j] == '\0' || argv[i][j] == '='))
		{		
			ft_dprintf(STDERR_FILENO, \
			"minishell: export: '%s': not a valid identifier\n", argv[i]);
			vars->exit_code = 1;
			return (-1);
		}
	}
	return (0);
}

static int	print_export(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->environ[i] != NULL)
	{
		printf("declare -x %s\n", vars->environ[i]);
		i++;
	}
	return (0);
}

int	exec_export(char *argv[], t_vars *vars)
{
	int		i;
	int		ret;
	char	*temp;

	if (argv[1] == NULL)
	{
		print_export(vars);
		return (0);
	}
	i = 1;
	while (argv[i] != NULL)
	{
		ret = check_chars(argv, vars, i);
		if (ret == 0)
		{
			temp = add_quote(argv[i]);
			allocate_new_env(temp, vars);
		}
		i++;
	}
	vars->exit_code = 0;
	return (0);
}
