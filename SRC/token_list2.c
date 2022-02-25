/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_list2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 13:22:17 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/02/25 16:30:58 by jobvan-d      ########   odam.nl         */
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

// removes a token from the list and frees it.
// be careful for use-after-frees when using this in a loop!
void	token_remove_from_list(t_token **tlst, t_token *to_remove)
{
	t_token	**tracer;

	tracer = tlst;
	while (*tracer && *tracer != to_remove)
	{
		tracer = &((*tracer)->next);
	}
	if (*tracer == to_remove)
	{
		*tracer = to_remove->next;
		if (*tracer)
		{
			(*tracer)->separated_from_previous
				= to_remove->separated_from_previous;
		}
		token_free(to_remove);
	}
}
