/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_pwd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 12:17:10 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/28 13:31:00 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*
	PWD: Print Working Directory
	It prints the directory you are in right now.
	There are some small edgecasses.
	If you use ANY flag. It should print: "pwd: bad option: *FLAG*"
	or "pwd: too many arguments".
*/

static void	add_oldpwd(t_vars *vars)
{
	int		i;
	char	**temp_env;

	i = 0;
	temp_env = vars->environ;
	while (temp_env[i] != NULL)
		i++;
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

static int	find_env_pwd(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->environ[i] != NULL)
	{
		if (ft_strncmp(vars->environ[i], "PWD=", 4) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	change_env_pwd(t_vars *vars)
{
	int		i;
	char	*temp;

	i = find_env_pwd(vars);
	if (i < 0)
		return (-1);
	temp = getcwd(NULL, 0);
	if (temp == NULL)
	{
		perror("getcwd");
		vars->exit_code = errno;
		return (vars->exit_code);
	}
	free(vars->environ[i]);
	vars->environ[i] = ft_strjoin("PWD=", temp);
	free(temp);
	return (0);
}

int	exec_pwd(char *argv[], t_vars *vars)
{
	if (argv != NULL)
	{
		if (vars->pwd != NULL)
			free(vars->pwd);
		vars->pwd = getcwd(NULL, 0);
		if (vars->pwd == NULL)
			vars->pwd = ft_getenv("PWD", vars->environ);
		ft_printf("%s\n", vars->pwd);
	}
	return (0);
}
