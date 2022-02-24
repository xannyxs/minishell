/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_expansion.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 14:36:18 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/02/24 17:11:46 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* ft_str* */

#include <stdlib.h> /* free */

/* looks up a variable. kind of specialized function, hence it's weird. */
static char	*var_lookup(const char *var, char **envp, size_t len)
{
	char	*value;

	value = NULL;
	while (*envp != NULL)
	{
		if (ft_strncmp(var, *envp, len) == 0 && (*envp)[len] == '=')
		{
			value = ft_strdup(*envp + len + 1);
			if (!value)
				fatal_perror("malloc");
			break ;
		}
		envp++;
	}
	return (value);
}

static size_t	count_var_length(const char *str)
{
	size_t	i;

	i = 1;
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9')
			|| (str[i] == '_'))
	)
	{
		i++;
	}
	return (i);
}

/* returns a and b joined, and frees both. Returns NULL on malloc fail. */
static char	*m_strfjoin(char *a, char *b)
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

static char	*get_part(size_t i, char **cstr, char **envp)
{
	size_t	var_length;
	char	*val;
	char	*tmp;

	var_length = count_var_length(*cstr + i);
	if (var_length == 1)
		i++;
	tmp = ft_strndup_unsafe(*cstr, i);
	if (!tmp)
		fatal_perror("malloc");
	*cstr += i;
	if (var_length > 1)
	{
		val = var_lookup(*cstr + 1, envp, var_length - 1);
		if (val)
		{
			tmp = m_strfjoin(tmp, val);
			if (!tmp)
				fatal_perror("malloc");
		}
		*cstr += var_length;
	}
	return (tmp);
}

static void	token_expand_finish(t_token *el, char *cstr, char *new_content)
{
	char	*tmp;

	if (*cstr)
	{
		tmp = ft_strjoin(new_content, cstr);
		free(new_content);
		if (!tmp)
			fatal_perror("malloc");
		new_content = tmp;
	}
	free(el->content);
	el->content = new_content;
}

// TODO: check leaks
// TODO: token should be REMOVED if there var lookup fails and is not quoted
// and no other text present.
void	expand_token(t_token *el, const t_vars *vars)
{
	size_t	i;
	char	*new_content;
	char	*cstr;

	cstr = el->content;
	new_content = NULL;
	while (1)
	{
		i = (size_t)ft_strchr(cstr, '$');
		if (i == 0)
			break ;
		i -= (size_t)cstr;
		new_content = m_strfjoin(new_content,
				get_part(i, &cstr, vars->environ));
		if (!new_content)
			fatal_perror("malloc");
	}
	if (new_content)
	{
		token_expand_finish(el, cstr, new_content);
	}
}
