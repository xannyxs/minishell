/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_env.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 22:18:38 by xander        #+#    #+#                 */
/*   Updated: 2022/03/09 17:17:44 by xander        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <unistd.h>

int	exec_env(char *argv[], t_vars *vars)
{
	int	i;

	i = 0;
	argv = NULL;
	vars->exit_code = 0;
	while (vars->environ[i] != NULL)
	{
		ft_putstr_fd(vars->environ[i], STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (0);
}
