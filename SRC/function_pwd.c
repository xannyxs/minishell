/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_pwd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 12:17:10 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/25 13:53:46 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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

int	change_env_pwd(t_vars *vars)
{
	int		i;

	i = find_env_pwd(vars);
	if (i < 0)
		return (-1);
	free(vars->environ[i]);
	vars->environ[i] = ft_strjoin("PWD=", getcwd(NULL, 1));
	return (0);
}

int	exec_pwd(t_vars *vars)
{
	free(vars->pwd);
	vars->pwd = getcwd(NULL, 1);
	if (vars->pwd == NULL || vars->token_list->next != NULL)
	{
		if (vars->token_list->next->token != T_PIPE)
		{
			ft_putstr_fd("pwd: bad option\n", STDERR_FILENO);
			return (errno);
		}
	}
	printf("%s\n", vars->pwd);
	change_env_pwd(vars);
	return (0);
}
