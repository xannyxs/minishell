/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   access_function.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:39:52 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/25 12:46:18 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

static int	path_row(char *envp[])
{
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (envp[i][0] == 'P')
		{
			if (ft_strncmp(envp[i], "PATH=", 5) == 0)
				return (i);
		}
		i++;
	}
	perror("ENV error"); // TODO
	return (-1);
}

char	**find_dir(char *envp[])
{
	int		i;
	char	**path;

	i = path_row(envp);
	if (i < 0)
		return (NULL);
	path = ft_split(envp[i], ':');
	if (path == NULL)
		return (NULL);
	return (path);
}

// TODO: I am fairly sure this will leak
char	*path_check(char *func, char **path)
{
	int		i;
	int		access_ok;
	char	*joined_path;

	i = 0;
	access_ok = -1;
	path[0] = ft_substr(path[0], 5, ft_strlen(path[0]) - 4);
	if (ft_strchr(func, ' ') != NULL)
		func = *ft_split(func, ' ');
	if (access(func, F_OK) == 0)
		return (func);
	while (path[i] != NULL && access_ok != 0)
	{
		joined_path = ft_strjoin(ft_strjoin(path[i], "/"), func);
		access_ok = access(joined_path, F_OK);
		i++;
	}
	if (access_ok == -1)
		return (NULL);
	return (joined_path);
}
