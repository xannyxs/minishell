/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   literal_splitting.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/28 17:19:47 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/29 16:18:50 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* ft_str* functions */

#include <stdlib.h> /* free */
#include <stdbool.h>

static void	add_wds(t_token **lst, char **wds)
{
	t_token	*tail;
	t_token	*new;

	tail = (*lst)->next;
	while (*wds)
	{
		new = token_new(*wds, T_LITERAL);
		if (!new)
			malloc_fail();
		(*lst)->next = new;
		*lst = new;
		wds++;
	}
	(*lst)->next = tail;
}

/* here the splitting is done. returns the rest of the list. */
static t_token	*m_split(t_token *lst)
{
	char	**wds;

	wds = ft_split(lst->content, ' ');
	if (wds == NULL)
		malloc_fail();
	if (*wds == NULL)
		*(lst->content) = '\0';
	else
	{
		free(lst->content);
		lst->content = *wds;
		add_wds(&lst, wds + 1);
	}
	free(wds);
	return (lst);
}

/* because this function is called after we know the string contains a space,
 * we don't have to check if the string has at least 1 char. */
static int	m_is_last_char_space(const char *str)
{
	return (*(str + ft_strlen(str) - 1) == ' ');
}

/* splits unqouted literals into separate literals if they contain spaces.
 * this is something weird but useful thing that bash does. */
void	split_literals_with_spaces(t_vars *vars)
{
	t_token	*lst;

	lst = vars->token_list;
	while (lst)
	{
		if (lst->token == T_LITERAL
			&& ft_str_contains_char(lst->content, ' '))
		{
			if (*(lst->content) == ' ')
				lst->separated_from_previous = true;
			if (lst->next && m_is_last_char_space(lst->content))
				lst->next->separated_from_previous = true;
			lst = m_split(lst);
		}
		lst = lst->next;
	}
}
