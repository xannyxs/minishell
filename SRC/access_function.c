/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   access_function.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:39:52 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/02 22:17:55 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i] != NULL)
	{
		free(path[i]);
		i++;
	}
	free(path);
}

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
	return (path);
}

char	*path_check(char *func, char **path)
{
	int		i;
	int		access_ok;
	char	*temp;
	char	*joined_path;

	i = 0;
	access_ok = -1;
	temp = path[0];
	path[0] = ft_substr(temp, 5, ft_strlen(path[0]) - 4);
	free(temp);
	if (ft_strchr(func, ' ') != NULL)
	{
		temp = func;
		func = *ft_split(temp, ' ');
		free(temp);
	}
	if (access(func, X_OK) == 0)
		return (func);
	while (path[i] != NULL && access_ok != 0)
	{
		temp = ft_strjoin(path[i], "/");
		joined_path = ft_strjoin(temp, func);
		access_ok = access(joined_path, X_OK);
		free(temp);
		if (access_ok == 0)
		{
			free_path(path);
			free(joined_path);
			return (joined_path);
		}
		free(joined_path);
		i++;
	}
	if (access_ok == -1)
		return (NULL);
	return (joined_path);
}
