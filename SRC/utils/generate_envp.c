/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   generate_envp.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/07 13:44:23 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/07 16:04:57 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* ft_memcpy, ft_strlen etc. */

#include <stdlib.h> /* malloc */

/* creates a `VAR=CONTENT' string from an envlist entry. */
static char	*create_environ_entry(const t_envlist *li)
{
	char	*result;
	size_t	var_len;
	size_t	content_len;

	var_len = ft_strlen(li->variable);
	content_len = ft_strlen(li->content);
	result = malloc(var_len + content_len + 1 + 1);
	if (!result)
		malloc_fail();
	ft_memcpy(result, li->variable, var_len);
	result[var_len] = '=';
	ft_memcpy(result + var_len + 1, li->content, content_len + 1);
	return (result);
}

static void	copy_user_vars_to_envp(char **envp, t_envlist *lst)
{
	while (lst)
	{
		*envp = create_environ_entry(lst);
		lst = lst->next;
		envp++;
	}
	*envp = NULL;
}

/* generates an char **envp from the vars, includes both user vars
 * and initial environ vars. Note that some of it is malloc'd and some of it
 * is borrowed from environ. This doesn't really matter because it is freed
 * by execve creates a new process image anyways.
 * ideally, you'd cache this result, allocate it properly, only redoing it
 * when a variable changes. This would require extensive changes though. */
char	**generate_envp(t_vars *vars)
{
	char	**envp;
	size_t	len;

	len = calc_envp_length(vars->environ);
	envp = malloc((len + envlist_len(vars->var_list) + 1) * sizeof(char *));
	if (!envp)
		malloc_fail();
	ft_memcpy(envp, vars->environ, len * sizeof(char *));
	copy_user_vars_to_envp(envp + len, vars->var_list);
	return (envp);
}
