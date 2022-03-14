/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_export.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 21:34:06 by xander        #+#    #+#                 */
/*   Updated: 2022/03/14 17:43:25 by xvoorvaa      ########   odam.nl         */
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
*/

static int	print_export(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->environ[i] != NULL)
	{
		printf("declare -x %s\n", vars->environ[i]);
		i++;
	}
	while (temp != NULL)
	{
		if (temp->content != NULL)
			printf("declare -x %s=\"%s\"\n", temp->variable, temp->content);
		else if (temp->content == NULL)
			printf("declare -x %s\n", temp->variable);
		else
			printf("declare -x %s=\"\"\n", temp->variable);
		temp = temp->next;
	}
	return (0);
}

static int	allocate_var(char *argv[], char **content, char **variable)
{
	*content = ft_strchr(argv[1], '=');
	if (*content != NULL)
	{
		*content = ft_substr(*content, 1, ft_strlen(*content) - 1);
		if (*content == NULL)
			fatal_perror("malloc");
	}
	*variable = ft_substr(argv[1], 0, ft_strequel(argv[1]));
	if (*variable == NULL)
		fatal_perror("malloc");
	return (0);
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
		vars->exit_code = allocate_var(argv, &content, &variable);
		if (vars->exit_code != 0)
			return (vars->exit_code);
		if (check_dup_env(*vars, variable) == true)
		{
			replace_dup_env(vars, variable, content);
			free(variable);
		}
		else
			new_node(&vars->var_list, variable, content);
		i++;
	}
	vars->exit_code = 0;
	return (0);
}
