/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_cd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 12:00:46 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/21 16:57:36 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
	EDGECASES:
	cd -
	cd .
	cd ../
	PWD & CD mixen is pretty annoooooyyyiingg
*/

/*
	STEPS OF MY CD:
	1. I first put the old PWD in vars->old_pwd, and get the new one.
	2. Check if I need to go to the HOME DIR.
	3. Otherwise check if "-" is being used.
	4. Do a normal CD.
*/

static int	change_homedir(t_vars vars)
{
	int	err;

	if (vars.token_list == NULL || vars.token_list->token == T_PIPE || \
		ft_strcmp(vars.token_list->content, "~") == 0)
	{
		err = chdir(getenv("HOME"));
		if (err != 0)
		{
			perror("cd");
			return (errno);
		}
		return (true);
	}
	return (false);
}

static int	change_dir(t_vars vars)
{
	int	err;

	if (ft_strcmp(vars.token_list->content, "-") == 0)
	{
		err = chdir(vars.old_pwd);
		if (err != 0)
		{
			perror("cd");
			return (errno);
		}
	}
	else
	{
		err = chdir(vars.token_list->content);
		if (err != 0)
		{
			perror("cd");
			return (errno);
		}
	}
	return (0);
}

int	exec_cd(t_vars *vars)
{
	vars->old_pwd = vars->pwd;
	vars->pwd = getcwd(NULL, 1);
	vars->token_list = vars->token_list->next;
	if (change_homedir(*vars) == true)
		return (0);
	if (vars->pwd == NULL)
		return (errno);
	if (change_dir(*vars) != 0)
		return (errno);
	return (0);
}
