/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_export.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 21:34:06 by xander        #+#    #+#                 */
/*   Updated: 2022/03/10 12:31:44 by xander        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdio.h>
#include <stdlib.h>

static int	ft_strequel(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '=' && str[len] != '\0')
		len++;
	return (len);
}

static int	print_export(t_vars *vars)
{
	int			i;
	t_envlist	*temp;

	i = 0;
	temp = vars->var_list;
	while (vars->environ[i] != NULL)
	{
		printf("declare -x %s\n", vars->environ[i]);
		i++;
	}
	while (temp != NULL)
	{
		printf("declare -x %s=\"%s\"\n", temp->variable, temp->content);
		temp = temp->next;
	}
	return (0);
}

int	exec_export(char *argv[], t_vars *vars)
{
	char		*variable;
	char		*content;
	int			i;

	if (argv[1] == NULL)
	{
		print_export(vars);
		return (0);
	}
	i = 1;
	while (argv[i] != NULL)
	{
		content = ft_strchr(argv[1], '=');
		if (content == NULL)
		{
			printf("bash: export: '%s': not a valid identifier\n", argv[1]);
			vars->exit_code = 1;
			return (EPERM);
		}
		content = ft_substr(content, 1, ft_strlen(content) - 1);
		variable = ft_substr(argv[1], 0, ft_strequel(argv[1]));
		if (content == NULL || variable == NULL)
		{
			printf("bash: export: '%s': not a valid identifier\n", argv[1]);
			vars->exit_code = 1;
			return (EPERM);
		}
		new_node(&vars->var_list, variable, content);
		i++;
	}
	return (0);
}
