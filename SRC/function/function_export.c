/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_export.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 21:34:06 by xander        #+#    #+#                 */
/*   Updated: 2022/03/21 20:06:36 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

/*
	First char of var = a-z A-Z or _
	rest of var = a-z A-Z or _ or 0-9
	"1hoi=fd" <-- Should not work

	Related with execute_single.c
	Functions in variables needs to be executed as well
	For example:
	export ls="ls -l"
	$ls - Prints out as if it is "ls -l"
*/

static void	print_error(char *argv)
{
	ft_dprintf(STDERR_FILENO, \
		"minishell: export: %s: not a valid identifier\n", argv);
}

static int	print_export(t_vars *vars)
{
	int			i;
	t_envlist	*temp;

	i = 0;
	temp = vars->var_list;
	while (vars->environ[i] != NULL)
	{
		print_sys_env(*vars, i);
		i++;
	}
	while (temp != NULL)
	{
		print_usr_env(temp);
		temp = temp->next;
	}
	return (0);
}

static void	allocate_var(char *argv, char **content, char **variable)
{
	*content = ft_strchr(argv, '=');
	if (*content != NULL)
	{
		*content = ft_substr(*content, 1, ft_strlen(*content) - 1);
		if (*content == NULL)
			fatal_perror("malloc");
	}
	*variable = ft_substr(argv, 0, ft_strequel(argv));
	if (*variable == NULL)
		fatal_perror("malloc");
}

static int	ft_valued_export_chars(char *argv)
{
	int	i;

	if (ft_isalpha(argv[0]) == false && argv[0] != '_')
		return (false);
	i = 0;
	while (argv[i] != '\0')
	{
		if (ft_isalnum(argv[i]) == false && argv[i] != '_' && argv[i] != '=')
			return (false);
		i++;
	}
	return (true);
}

int	exec_export(char *argv[], t_vars *vars)
{
	int			i;
	char		*variable;
	char		*content;

	if (argv[1] == NULL)
		return (print_export(vars));
	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_strlen(argv[i]) > 0 && ft_valued_export_chars(argv[i]) == true)
		{
			allocate_var(argv[i], &content, &variable);
			if (check_dup_env(*vars, variable) == true)
			{
				replace_dup_env(vars, variable, content);
				free(variable);
			}
			else
				new_node(&vars->var_list, variable, content);
		}
		else
			print_error(argv[i]);
		i++;
	}
	return (0);
}
