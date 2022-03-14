/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_list2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 13:22:17 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/04 12:39:19 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* removes the last element from the loken list and returns it.
 * Does NOT delete/free it. */
t_token	*token_li_pop_back(t_token **tlst)
{
	t_token	**tracer;
	t_token	*to_return;

	tracer = tlst;
	to_return = NULL;
	if (*tracer)
	{
		while ((*tracer)->next)
		{
			tracer = &((*tracer)->next);
		}
		to_return = *tracer;
		*tracer = NULL;
	}
	return (to_return);
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

/* converts the token list from singly linked to doubly linked. */
void	token_make_list_doubly_linked(t_token *lst)
{
	t_token	*prev;

	prev = NULL;
	while (lst)
	{
		lst->prev = prev;
		prev = lst;
		lst = lst->next;
	}
}

/* loops over the list, calls function f with the current token, and adds the
 * result to sum, returns the sum. */
int	token_count_occurrences(t_token *lst, int (*f)(t_token *))
{
	int	sum;

	sum = 0;
	while (lst)
	{
		sum += (*f)(lst);
		lst = lst->next;
	}
	return (sum);
}

/* loops over the list, calls function f with the current token,
 * returns the first one it sees. Else it returns NULL. */
t_token	*token_get_first_occurrence(t_token *lst, int (*f)(t_token *))
{
	while (lst)
	{
		if ((*f)(lst))
		{
			return (lst);
		}
		lst = lst->next;
	}
	return (lst);
}
