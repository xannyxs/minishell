/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   allocate_env.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/14 21:18:01 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/14 21:21:48 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdlib.h> /* Malloc */

/*
	Mallocs the env of the last terminal.
	If it sees OLDPWD. It will make it empty.
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
		if (ft_strncmp(environ[i], "OLDPWD", 6) == 0)
			vars->environ[i] = ft_strdup("OLDPWD=");
		else
			vars->environ[i] = ft_strdup(environ[i]);
		if (vars->environ[i] == NULL)
			fatal_perror("malloc");
		i++;
	}
	vars->environ[i] = NULL;
}
