/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_expansion_util.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/21 18:23:51 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/31 13:42:31 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* ft_str*, ft_uitoa */

#include <stdlib.h> /* free */

/* inner part of var lookup, does lookup in user vars */
static void	m_var_lookup_uservar(t_envlist *lst,
	char **value, const char *var, size_t len)
{
	while (lst != NULL)
	{	
		if (ft_strncmp(var, lst->variable, len) == 0
			&& lst->variable[len] == '\0')
		{
			if (lst->content != NULL)
			{
				*value = ft_strdup(lst->content);
				if (!*value)
					malloc_fail();
			}
			break ;
		}
		lst = lst->next;
	}
}

/* looks up a variable. kind of specialized function, hence it's weird.
 * you cannot replace the environ lookup with ft_getenv, as it would
 * check the entire string, rather stop at len. */
static char	*var_lookup(const char *var, const t_vars *vars, size_t len)
{
	char		*value;
	char		**envp;

	if (*var == '?')
	{
		value = ft_uitoa(vars->exit_code);
		if (!value)
			malloc_fail();
		return (value);
	}
	value = NULL;
	envp = vars->environ;
	while (*envp != NULL)
	{
		if (ft_strncmp(var, *envp, len) == 0 && (*envp)[len] == '=')
		{
			value = ft_strdup(*envp + len + 1);
			if (!value)
				malloc_fail();
			return (value);
		}
		envp++;
	}
	m_var_lookup_uservar(vars->var_list, &value, var, len);
	return (value);
}

/* counts the length of a variable str. i.e. $hello!!! returns 6. */
static size_t	count_var_length(const char *str)
{
	size_t	i;

	i = 1;
	if (str[i] == '?')
	{
		i++;
		return (i);
	}
	while ((str[i] >= 'a' && str[i] <= 'z')
		|| (str[i] >= 'A' && str[i] <= 'Z')
		|| (str[i] >= '0' && str[i] <= '9')
		|| (str[i] == '_')
	)
	{
		i++;
	}
	return (i);
}

/* returns a and b joined, and frees both. Returns NULL on malloc fail. */
char	*ve_strfjoin(char *a, char *b)
{
	char	*tmp;

	if (a == NULL)
	{
		tmp = ft_strdup(b);
	}
	else
	{
		tmp = ft_strjoin(a, b);
		free(a);
	}
	free(b);
	return (tmp);
}

/* returns a part. i is where the variable stars, i.e. the index of the `$'.
 * Returns everything prior to the variable plus the variable itself. */
char	*ve_get_part(size_t i, char **cstr, const t_vars *vars)
{
	char	*val;
	char	*tmp;
	size_t	var_length;

	var_length = count_var_length(*cstr + i);
	if (var_length == 1)
		i++;
	tmp = ft_strndup_unsafe(*cstr, i);
	if (!tmp)
		malloc_fail();
	*cstr += i;
	if (var_length > 1)
	{
		val = var_lookup(*cstr + 1, vars, var_length - 1);
		if (val)
		{
			tmp = ve_strfjoin(tmp, val);
			if (!tmp)
				malloc_fail();
		}
		*cstr += var_length;
	}
	return (tmp);
}
