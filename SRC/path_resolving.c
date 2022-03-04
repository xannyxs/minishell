/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_resolving.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/03 14:10:19 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/04 12:31:56 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* most of this is more or less stolen from my pipex lel */
#include "minishell.h"
#include "libft.h" /* libft string functions */

#include <stdlib.h> /* free */
#include <unistd.h> /* access */

#define PATH_ENTRY ("PATH=")

/* tries to get a null-terminated string array of paths. Returns NULL
 * it fails(i.e. if there isn't any). Otherwise it is guaranteed that
 * the returned value is not empty. */
static char	**get_paths_array(char **envp)
{
	char	**ret;

	while (*envp && ft_strncmp(*envp, PATH_ENTRY, ft_strlen(PATH_ENTRY)) != 0)
	{
		envp++;
	}
	if (!*envp)
	{
		return (NULL);
	}
	ret = ft_split(*envp + ft_strlen(PATH_ENTRY), ':');
	if (!ret)
	{
		fatal_perror("malloc ft_split in get_paths_array");
	}
	else if (*ret == 0)
	{
		free(ret);
		ret = NULL;
	}
	return (ret);
}

/* appends slashes if neccessary to the null-terminated string array of paths.
 */
static void	append_slash_paths(char **paths)
{
	char	*tmp;

	while (*paths)
	{
		tmp = *paths;
		if (*(tmp + ft_strlen(tmp) - 1) != '/')
		{
			*paths = ft_strjoin(tmp, "/");
			free(tmp);
			if (!*paths)
			{
				fatal_perror("malloc ft_strjoin in append_slash_paths");
			}
		}
		paths++;
	}
}

static char	*try_command(char *file, const char *path)
{
	char	*ret;

	ret = ft_strjoin(path, file);
	if (!ret)
	{
		fatal_perror("malloc ft_strjoin in try_command");
	}
	if (access(ret, X_OK) == 0)
	{
		return (ret);
	}
	free(ret);
	return (NULL);
}

/* tries to find a working executable path for program_name, using PATH from 
 * envp. Does NOT check for built-ins. Also does NOT check local directory
 * itself.
 * Returns NULL on failure, otherwise returns a newly malloc'd
 * exec path. */
static char	*tryfind(char *program_name, char **envp)
{
	char	*ret;
	char	**paths;
	char	**orig_paths;

	paths = get_paths_array(envp);
	if (paths)
	{
		orig_paths = paths;
		append_slash_paths(paths);
		while (*paths)
		{
			ret = try_command(program_name, *paths);
			if (ret)
			{
				ft_free_str_arr(orig_paths);
				return (ret);
			}
			paths++;
		}
		ft_free_str_arr(orig_paths);
	}
	return (NULL);
}

/* returns a newly malloc'd full path for program name if it's found.
 * if it isn't, returns just the program */
char	*pathresolve_tryfind(char *name, char **envp)
{
	char	*ret;

	if (ft_strchr(name, '/') == NULL)
	{
		ret = tryfind(name, envp);
	}
	else
	{
		ret = name;
	}
	return (ret);
}
