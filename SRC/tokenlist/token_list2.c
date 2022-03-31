/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_list2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 13:22:17 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/31 13:55:59 by jobvan-d      ########   odam.nl         */
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

/* loops over the list, calls function f with the current token,
 * returns the first one it sees. Else it returns NULL. */
t_token	*token_get_first_occurrence(t_token *lst, int (*f)(const t_token *))
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

/* returns 1 if token is a type of redirect. */
int	token_is_redirect(const t_token *tok)
{
	return (tok->token == T_REDIRECT_FILE_TO_STDIN
		|| tok->token == T_REDIRECT_STDOUT_TO_FILE
		|| tok->token == T_REDIRECT_STDOUT_TO_FILE_APPEND
		|| tok->token == T_HEREDOC);
}
