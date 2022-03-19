/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_export.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 21:34:06 by xander        #+#    #+#                 */
/*   Updated: 2022/03/19 15:18:49 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"

#include <stdio.h>
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

static void	print_sys_env(t_vars vars, int i)
{
	char	**split_env;

	split_env = ft_split(vars.environ[i], '=');
	if (split_env == NULL)
		fatal_perror("malloc");
	if (split_env[1] == NULL)
		printf("declare -x %s=\"\"\n", split_env[0]);
	else
		printf("declare -x %s=\"%s\"\n", split_env[0], split_env[1]);
	ft_free_str_arr(split_env);
}

static void	print_usr_env(t_envlist *temp)
{
	if (temp->content != NULL)
		printf("declare -x %s=\"%s\"\n", temp->variable, temp->content);
	else if (temp->content == NULL)
		printf("declare -x %s\n", temp->variable);
	else
		printf("declare -x %s=\"\"\n", temp->variable);
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
		if (ft_strlen(argv[i]) > 0)
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
			ft_dprintf(STDERR_FILENO, \
			"minishell: export: %s: not a valid identifier\n", argv[i]);
		i++;
	}
	return (0);
}
