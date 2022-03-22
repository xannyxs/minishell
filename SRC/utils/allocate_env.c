/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   allocate_env.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/14 21:18:01 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/22 13:33:37 by xvoorvaa      ########   odam.nl         */
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

static void	malloc_env(t_vars *vars, char **environ)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
		i++;
	vars->environ = malloc((i + 1) * sizeof(char *));
	if (vars->environ == NULL)
		fatal_perror("malloc");
}

/*
	Mallocs the env of the last terminal.
	If it sees OLDPWD. It will make it empty.
	If it sees SHLVL. It will increment one more time.
*/
void	allocate_env(t_vars *vars)
{
	int			i;
	char		*temp;
	extern char	**environ;

	malloc_env(vars, environ);
	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], "OLDPWD=", 7) == 0)
			vars->environ[i] = ft_strdup("OLDPWD=");
		else if (ft_strncmp(environ[i], "SHLVL=", 6) == 0)
		{
			temp = increment_shlvl(environ[i]);
			vars->environ[i] = ft_strjoin("SHLVL=", temp);
			free(temp);
		}
		else
			vars->environ[i] = ft_strdup(environ[i]);
		if (vars->environ[i] == NULL)
			fatal_perror("malloc");
		i++;
	}
	vars->environ[i] = NULL;
}
