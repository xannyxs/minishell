/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_env.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 22:18:38 by xander        #+#    #+#                 */
/*   Updated: 2022/03/30 15:16:00 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h" /* ft_dprintf */

#include <unistd.h> /* STDs */

static int	error_handeling(char *argv)
{
	ft_dprintf(STDERR_FILENO, "env: %s: No such file or directory\n", \
	argv);
	return (127 + (errno == 2));
}

int	exec_env(char *argv[], t_vars *vars)
{
	int			i;
	t_envlist	*temp;

	i = 0;
	temp = vars->var_list;
	if (ft_getargc(argv) > 1)
		return (error_handeling(argv[1]));
	while (vars->environ[i] != NULL)
	{
		ft_printf("%s\n", vars->environ[i]);
		i++;
	}
	while (temp != NULL)
	{
		if (temp->content != NULL)
			ft_printf("%s=%s\n", temp->variable, temp->content);
		temp = temp->next;
	}
	return (SUCCESS);
}
