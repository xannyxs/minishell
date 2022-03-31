/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_cd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 12:00:46 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/31 11:59:39 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* Strcmp */
#include "ft_printf.h" /* ft_dprintf */

#include <unistd.h> /* STD & write */
#include <stdlib.h> /* Free & malloc */
#include <stdio.h> /* Perror */

/*
	STEPS OF MY CD:
	1. I first put the old PWD in vars->old_pwd, and get the new one.
	2. Check if I need to go to the HOME DIR.
	3. Otherwise check if "-" is being used.
	4. Do a normal CD.

	LEAK FREE
*/

static int	nonfatal_error(char *argv[])
{
	ft_dprintf(STDERR_FILENO, "minishell: cd: %s", argv[1]);
	perror(" ");
	return (-1);
}

static int	change_homedir(char *argv[], char *environ[], t_vars *vars)
{
	int		err;
	char	*home;

	home = ft_getenv("HOME", environ);
	if (home == NULL)
	{
		if (ft_strcmp(argv[0], "cd") == 0 && argv[1] == NULL)
		{
			ft_dprintf(STDERR_FILENO, "minishell: cd: HOME not set\n");
			return (-1);
		}
		return (false);
	}
	if ((argv[1] != NULL && ft_strcmp(argv[1], home) == 0) || \
		(ft_strcmp(argv[0], "cd") == 0 && argv[1] == NULL))
	{
		change_env_oldpwd(vars);
		err = chdir(home);
		free(home);
		if (err != 0)
			return (nonfatal_error(argv));
		return (true);
	}
	free(home);
	return (false);
}

static int	change_dir(char *argv[], t_vars vars)
{
	int		err;

	if (ft_strcmp(argv[1], "-") == 0)
	{
		err = chdir(vars.old_pwd);
		if (err == 0)
			ft_printf("%s\n", vars.old_pwd);
	}
	else
		err = chdir(argv[1]);
	if (err != 0)
		return (nonfatal_error(argv));
	return (0);
}

static int	examine_input(t_vars *vars, char *argv[], char **temp_pwd)
{
	if (vars->old_pwd == NULL && ft_strcmp(argv[1], "-") == 0)
	{
		ft_dprintf(STDERR_FILENO, "minishell: cd: OLDPWD not set\n");
		return (-1);
	}
	else if (ft_strcmp(argv[1], "-") != 0)
	{
		if (vars->old_pwd != NULL)
			free(vars->old_pwd);
		vars->old_pwd = ft_getenv("PWD", vars->environ);
		change_env_oldpwd(vars);
	}
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		temp_pwd[0] = ft_getenv("PWD", vars->environ);
		return (1);
	}
	return (0);
}

int	exec_cd(char *argv[], t_vars *vars)
{
	int			ret;
	int			check_dash;
	char		*temp_pwd;

	ret = change_homedir(argv, vars->environ, vars);
	if (ret == true)
		return (change_env_pwd(vars));
	else if (ret == -1)
		return (ERROR);
	check_dash = examine_input(vars, argv, &temp_pwd);
	if (check_dash == -1)
		return (ERROR);
	if (change_dir(argv, *vars) != 0)
		return (ERROR);
	if (check_dash == 1)
	{
		free(vars->old_pwd);
		vars->old_pwd = temp_pwd;
	}
	change_env_pwd(vars);
	return (0);
}
