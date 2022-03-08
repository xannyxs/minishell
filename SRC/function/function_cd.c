/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_cd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 12:00:46 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/08 15:51:06 by xander        ########   odam.nl         */
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

static int	change_homedir(t_token *token_list, char *environ[])
{
	int		err;
	char	*home;

	if (token_list->token == T_PIPE || \
		ft_strcmp(token_list->content, "~") == 0 || \
		ft_strcmp(token_list->content, "cd") == 0)
	{
		home = ft_getenv("HOME", environ);
		err = chdir(home);
		free(home);
		if (err != 0)
		{
			write(STDERR_FILENO, "minishell: cd: ", 11);
			write(STDERR_FILENO, token_list->content, ft_strlen(token_list->content));
			perror(" ");
			write(STDERR_FILENO, "\n", 1);
			return (errno);
		}
		return (true);
	}
	return (false);
}

static int	change_dir(t_vars vars, t_token *temp)
{
	int		err;

	if (ft_strcmp(temp->content, "-") == 0)
	{
		err = chdir(vars.old_pwd);
		if (err == 0)
			printf("%s\n", vars.old_pwd);
	}
	else
		err = chdir(temp->content);
	if (err != 0)
	{
		write(STDERR_FILENO, "minishell: cd: ", 16);
		write(STDERR_FILENO, temp->content, ft_strlen(temp->content));
		perror(" ");
		return (errno);
	}
	return (0);
}

static int	examine_cd(t_vars *vars, t_token *temp, char **temp_pwd)
{
	if (vars->old_pwd == NULL && ft_strcmp(temp->content, "-") == 0)
	{
		write(STDERR_FILENO, "minishell: cd: OLDPWD not set\n", 31);
		errno = EPERM;
		return (-1);
	}
	else if (ft_strcmp(temp->content, "-") != 0)
	{
		if (vars->old_pwd != NULL)
			free(vars->old_pwd);
		vars->old_pwd = ft_getenv("PWD", vars->environ);
		change_env_oldpwd(vars);
	}
	else if (ft_strcmp(temp->content, "-") == 0)
	{
		temp_pwd[0] = ft_getenv("PWD", vars->environ);
		return (1);
	}
	return (0);
}

int	exec_cd(t_vars *vars)
{
	int			check_dash;
	char		*temp_pwd;
	t_token		*temp;

	if (vars->token_list->next != NULL)
		temp = vars->token_list->next;
	else
		temp = vars->token_list;
	check_dash = examine_cd(vars, temp, &temp_pwd);
	if (check_dash == -1)
		return (errno);
	if (change_homedir(temp, vars->environ) == true)
	{
		change_env_pwd(vars);
		return (0);
	}
	if (change_dir(*vars, temp) != 0)
		return (errno);
	if (check_dash == 1)
	{
		free(vars->old_pwd);
		vars->old_pwd = temp_pwd;
	}
	change_env_pwd(vars);
	return (0);
}
