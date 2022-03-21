/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   allocate_env.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/14 21:18:01 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/21 20:19:57 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdlib.h> /* Malloc */
#include <stdio.h>

static char	*increment_shlvl(char *environ)
{
	int		layer_shell;
	char	*shlvl;

	shlvl = ft_strchr(environ, '=') + 1;
	layer_shell = ft_atoi(shlvl) + 1;
	shlvl = ft_itoa(layer_shell);
	return (shlvl);
}

/*
	Mallocs the env of the last terminal.
	If it sees OLDPWD. It will make it empty.
	If it sees SHLVL. It will increment one more time.
*/
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
		if (ft_strncmp(environ[i], "OLDPWD=", 7) == 0)
			vars->environ[i] = ft_strdup("OLDPWD=");
		else if (ft_strncmp(environ[i], "SHLVL=", 6) == 0)
			vars->environ[i] = ft_strjoin("SHLVL=", \
				increment_shlvl(environ[i]));
		else
			vars->environ[i] = ft_strdup(environ[i]);
		if (vars->environ[i] == NULL)
			fatal_perror("malloc");
		i++;
	}
	vars->environ[i] = NULL;
}
