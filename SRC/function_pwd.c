/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_pwd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 12:17:10 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/22 18:45:59 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	find_env_pwd(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->environ[i] != NULL)
	{
		if (ft_strncmp(vars->environ[i], "PWD", 3) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	exec_pwd(t_vars *vars)
{
	int	i;
	char *env_pwd;

	free(vars->pwd);
	vars->pwd = getcwd(NULL, 1);
	if (vars->pwd == NULL)
	{
		printf("pwd: bad option\n");
		return (errno);
	}
	printf("%s\n", vars->pwd);
	i = find_env_pwd(vars);
	if (i < 0)
		return (-1);
	env_pwd = ft_strjoin("PWD=", vars->pwd);
	ft_memcpy(vars->environ[i], env_pwd, ft_strlen(vars->environ[i]));
	free(env_pwd);
	return (0);
}
