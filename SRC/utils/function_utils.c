/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/09 12:42:49 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/11 16:17:01 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "function.h"
#include "libft.h" /* ft_strcmp */

#include <unistd.h> /* close */

t_function	get_function(const char *name)
{
	const t_function	funcs[] = {
	{"echo", &exec_echo, 1},
	{"cd", &exec_cd, 0},
	{"pwd", &exec_pwd, 1},
	{"export", &exec_export, 0},
	{"unset", &exec_unset, 0},
	{"env", &exec_env, 1},
	{"exit", &exec_exit, 0},
	{0, NULL, 0}
	};
	int					i;

	i = 0;
	while (funcs[i].key != NULL)
	{
		if (ft_strcmp(funcs[i].key, name) == 0)
		{
			return (funcs[i]);
		}
		i++;
	}
	return (funcs[i]);
}

/* closes a file descriptor if it's not -1 */
void	ft_close_fd(const int fd)
{
	if (fd != -1)
	{
		close(fd);
	}
}
