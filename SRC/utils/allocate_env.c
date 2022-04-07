/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   allocate_env.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/14 21:18:01 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/04/07 15:51:34 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* ft_atoi */

#include <stdlib.h> /* malloc */

/* returns the length of a char** */
size_t	calc_envp_length(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		i++;
	}
	return (i);
}

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
	char		*temp;
	extern char	**environ;

	vars->environ = malloc((calc_envp_length(environ) + 1) * sizeof(char *));
	if (vars->environ == NULL)
		malloc_fail();
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
			malloc_fail();
		i++;
	}
	vars->environ[i] = NULL;
}
