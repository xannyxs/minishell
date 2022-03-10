/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   allocation_env.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/10 16:23:26 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/10 16:30:25 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
