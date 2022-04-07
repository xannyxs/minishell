/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   oldpwd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/28 18:11:20 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/04/07 18:00:50 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* ft_strcmp */

#include <stdlib.h> /* Free & malloc */
#include <unistd.h> /* Getcwd */

static void	add_oldpwd(t_vars *vars)
{
	size_t	i;
	char	**temp_env;

	temp_env = vars->environ;
	i = calc_envp_length(temp_env);
	vars->environ = malloc((i + 2) * sizeof(char *));
	if (vars->environ == NULL)
		fatal_perror("malloc");
	i = 0;
	while (temp_env[i] != NULL)
	{
		vars->environ[i] = temp_env[i];
		i++;
	}
	vars->environ[i] = "OLDPWD=";
	vars->environ[i + 1] = NULL;
	free(temp_env);
}

static int	find_env_oldpwd(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->environ[i] != NULL)
	{
		if (ft_strncmp(vars->environ[i], "OLDPWD=", 7) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	change_env_oldpwd(t_vars *vars)
{
	int	i;

	i = find_env_oldpwd(vars);
	if (i < 0)
	{
		add_oldpwd(vars);
		i = find_env_oldpwd(vars);
	}
	else
		free(vars->environ[i]);
	if (vars->old_pwd == NULL)
		vars->old_pwd = getcwd(NULL, 0);
	vars->environ[i] = ft_strjoin("OLDPWD=", vars->old_pwd);
	if (vars->environ[i] == NULL)
		malloc_fail();
	return (0);
}
