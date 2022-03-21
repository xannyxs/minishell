/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_env.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 22:18:38 by xander        #+#    #+#                 */
/*   Updated: 2022/03/21 20:52:35 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"

#include <unistd.h>
#include <stdio.h>

static int	error_handeling(t_vars *vars, char *argv)
{
	ft_dprintf(STDERR_FILENO, "env: %s: No such file or directory\n", \
	argv);
	vars->exit_code = 127 + (errno == 2);
	return (vars->exit_code);
}

int	exec_env(char *argv[], t_vars *vars)
{
	int			i;
	t_envlist	*temp;

	i = 0;
	temp = vars->var_list;
	vars->exit_code = 0;
	if (ft_getargc(argv) > 1)
		return (error_handeling(vars, argv[1]));
	while (vars->environ[i] != NULL)
	{
		ft_putstr_fd(vars->environ[i], STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	while (temp != NULL)
	{
		if (temp->content != NULL)
			printf("%s=%s\n", temp->variable, temp->content);
		temp = temp->next;
	}
	return (0);
}
