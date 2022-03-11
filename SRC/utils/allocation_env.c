/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   allocation_env.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/10 16:23:26 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/10 18:18:13 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdlib.h>
#include <stdio.h>

/* allocates first time env */
void	allocate_env(t_vars *vars)
{
	int			i;
	extern char	**environ;

	i = 0;
	while (environ[i] != NULL)
		i++;
	vars->environ = malloc((i + 1) * sizeof(char *));
	if (vars->environ == NULL)
		fatal_perror("malloc");
	i = 0;
	while (environ[i] != NULL)
	{
		vars->environ[i] = ft_strdup(environ[i]);
		if (vars->environ[i] == NULL)
			fatal_perror("malloc");
		i++;
	}
	vars->environ[i] = NULL;
}

void	allocate_new_env(char *new_var, t_vars *vars)
{
	int		i;
	char	**new_environ;

	i = 0;
	while (vars->environ[i] != NULL)
		i++;
	new_environ = malloc(sizeof(char *) * (i + 2));
	if (vars->environ == NULL)
		fatal_perror("malloc");
	i = 0;
	while (vars->environ[i] != NULL)
	{
		new_environ[i] = vars->environ[i];
		i++;
	}
	new_environ[i] = new_var;
	new_environ[i + 1] = NULL;
	free(vars->environ);
	vars->environ = new_environ;
}
