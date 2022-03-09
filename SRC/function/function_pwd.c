/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_pwd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 12:17:10 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/09 12:47:41 by jobvan-d      ########   odam.nl         */
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

int	change_env_oldpwd(t_vars *vars)
{
	int		i;

	i = find_env_oldpwd(vars);
	if (i < 0)
		return (-1);
	free(vars->environ[i]);
	if (vars->old_pwd == NULL)
		vars->old_pwd = getcwd(NULL, 1);
	vars->environ[i] = ft_strjoin("OLDPWD=", vars->old_pwd);
	if (vars->environ[i] == NULL)
		fatal_perror("malloc");
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
	temp = getcwd(NULL, 1);
	free(vars->environ[i]);
	vars->environ[i] = ft_strjoin("PWD=", temp);
	free(temp);
	return (0);
}

int	exec_pwd(char **argv, t_vars *vars)
{
	if (vars->pwd != NULL)
		free(vars->pwd);
	vars->pwd = getcwd(NULL, 1);
	if (vars->pwd == NULL || vars->token_list->next != NULL)
	{
		if (vars->token_list->next->token != T_PIPE)
		{
			ft_dprintf(STDERR_FILENO, "pwd: bad option\n");
			return (errno);
		}
	}
	printf("%s\n", vars->pwd);
	change_env_pwd(vars);
	return (0);
}
