/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_cd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 12:00:46 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/25 13:53:00 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
	STEPS OF MY CD:
	1. I first put the old PWD in vars->old_pwd, and get the new one.
	2. Check if I need to go to the HOME DIR.
	3. Otherwise check if "-" is being used.
	4. Do a normal CD.

	LEAK FREE
*/

static int	find_env_oldpwd(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->environ[i] != NULL)
	{
		if (ft_strncmp(vars->environ[i], "OLDPWD", 6) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	change_env_oldpwd(t_vars *vars)
{
	int		i;

	i = find_env_oldpwd(vars);
	if (i < 0)
		return (-1);
	free(vars->environ[i]);
	if (vars->old_pwd == NULL)
		vars->old_pwd = getcwd(NULL, 1);
	vars->environ[i] = ft_strjoin("OLDPWD=", vars->old_pwd);
	return (0);
}

static int	change_homedir(t_token *vars)
{
	int	err;

	if (vars == NULL || vars->token == T_PIPE || \
		ft_strcmp(vars->content, "~") == 0)
	{
		err = chdir(getenv("HOME"));
		if (err != 0)
		{
			perror("cd");
			return (EPERM);
		}
		return (true);
	}
	return (false);
}

static int	change_dir(t_vars vars, t_token *temp)
{
	int	err;

	if (ft_strcmp(temp->content, "-") == 0)
	{
		err = chdir(vars.old_pwd);
		if (err != 0)
		{
			perror("cd");
			return (EPERM);
		}
	}
	else
	{
		err = chdir(temp->content);
		if (err != 0)
		{
			perror("cd");
			return (EPERM);
		}
	}
	return (0);
}

int	exec_cd(t_vars *vars)
{
	t_token	*temp;

	vars->pwd = getcwd(NULL, 1);
	vars->old_pwd = vars->pwd;
	change_env_oldpwd(vars);
	temp = vars->token_list->next;
	if (change_homedir(temp) == true)
	{
		change_env_pwd(vars);
		return (0);
	}
	if (vars->pwd == NULL)
		return (errno);
	if (change_dir(*vars, temp) != 0)
		return (EPERM);
	change_env_pwd(vars);
	return (0);
}
