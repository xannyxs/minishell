/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_pwd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 12:17:10 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/23 13:44:30 by jobvan-d      ########   odam.nl         */
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
	Check in your list if you use cd in a pipe.
*/

int	exec_pwd(t_vars *vars)
{
	vars->pwd = getcwd(NULL, 1);
	if (vars->pwd == NULL)
	{
		ft_putendl_fd("pwd: bad option\n", 2);
		return (errno);
	}
	printf("%s\n", vars->pwd);
	return (0);
}
