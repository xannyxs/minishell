/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_export.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 21:34:06 by xander        #+#    #+#                 */
/*   Updated: 2022/04/05 16:55:19 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* Several functions */
#include "ft_printf.h" /* ft_dprintf */

#include <stdlib.h> /* free */
#include <unistd.h> /* STD */

static void	nonfatal_error(t_vars *vars, char *argv)
{
	ft_dprintf(STDERR_FILENO, \
		"minishell: export: %s: not a valid identifier\n", argv);
	vars->exit_code = 1;
}

static int	print_export(t_vars *vars)
{
	t_envlist	*temp;

	temp = vars->var_list;
	order_sys_env(*vars);
	order_usr_env(temp);
	return (SUCCESS);
}

static void	allocate_var(char *argv, char **content, char **variable)
{
	*content = ft_strchr(argv, '=');
	if (*content != NULL)
	{
		*content = ft_strdup(*content + 1);
		if (*content == NULL)
			malloc_fail();
	}
	*variable = ft_substr(argv, 0, ft_strequel(argv));
	if (*variable == NULL)
		malloc_fail();
}

static void	add_var_to_env(t_vars *vars, char *argv)
{
	char	*variable;
	char	*content;

	if (ft_is_valid_setarg(argv) == true)
	{
		allocate_var(argv, &content, &variable);
		if (check_dup_env(*vars, variable) == true)
		{
			replace_dup_env(vars, variable, content);
			free(variable);
		}
		else
			new_node(&vars->var_list, variable, content);
	}
	else
		nonfatal_error(vars, argv);
}

int	exec_export(char *argv[], t_vars *vars)
{
	int	i;

	vars->exit_code = 0;
	if (argv[1] == NULL)
		return (print_export(vars));
	i = 1;
	while (argv[i] != NULL)
	{
		add_var_to_env(vars, argv[i]);
		i++;
	}
	return (vars->exit_code);
}
