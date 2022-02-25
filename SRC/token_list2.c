/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_list2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 13:22:17 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/02/25 14:32:09 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>

/* TODO: lstiter? */

t_token	*token_li_pop_back(t_token **tlst)
{
	t_token	*li;
	t_token	*prev;

	li = *tlst;
	if (!li)
		return (NULL);
	else if (!li->next)
	{
		*tlst = NULL;
		return (li);
	}
	prev = li;
	while (li->next)
	{
		prev = li;
		li = li->next;
	}
	prev->next = NULL;
	return (li);
}

// removes to_remove from the token list. WILL SEGFAULT IF TO_REMOVE IS NULL
void	token_remove_from_list(t_token **tlst, t_token *to_remove)
{
	t_token	*cur;

	cur = *tlst;
	if (cur == to_remove)
	{
		if (cur->next)
			cur->next->separated_from_previous
				= to_remove->separated_from_previous;
		*tlst = cur->next;
		token_free(to_remove);
		return ;
	}
	while (cur)
	{
		if (cur->next == to_remove)
		{
			cur->next = to_remove->next;
			if (cur->next)
				cur->next->separated_from_previous
					= to_remove->separated_from_previous;
			token_free(to_remove);
			break ;
		}
		cur = cur->next;
	}
}
