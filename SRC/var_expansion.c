/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_expansion.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 14:36:18 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/30 14:48:35 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* ft_str*, ft_uitoa */

#include <stdlib.h> /* free */

/* expands the tilde at the beginning of the word. Assumes there is a ~. */
static void	expand_tilde(t_token *el, const t_vars *vars)
{
	char	*new;
	char	*home;

	home = ft_getenv("HOME", vars->environ);
	if (!home)
		home = "";
	new = ft_strjoin(home, el->content + 1);
	if (!new)
		malloc_fail();
	free(el->content);
	el->content = new;
}

static void	token_expand_finish(t_token *el, char *cstr, char *new_content)
{
	char	*tmp;

	if (*cstr)
	{
		tmp = ft_strjoin(new_content, cstr);
		free(new_content);
		if (!tmp)
			malloc_fail();
		new_content = tmp;
	}
	free(el->content);
	el->content = new_content;
}

// TODO:	Check leaks
void	expand_token(t_token *el, const t_vars *vars)
{
	size_t	i;
	char	*new_content;
	char	*cstr;

	if (*el->content == '~')
		expand_tilde(el, vars);
	cstr = el->content;
	new_content = NULL;
	while (true)
	{
		i = (size_t)ft_strchr(cstr, '$');
		if (i == 0)
			break ;
		i -= (size_t)cstr;
		new_content = ve_strfjoin(new_content, ve_get_part(i, &cstr, vars));
		if (!new_content)
			malloc_fail();
	}
	if (new_content)
		token_expand_finish(el, cstr, new_content);
}
