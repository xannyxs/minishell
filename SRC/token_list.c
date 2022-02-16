/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 16:16:23 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/02/16 17:40:01 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h> /* malloc, free */

/* creates a new token list element. Returns a pointer to the token on 
 * success, NULL on malloc fail. */
t_token	*token_new(char *content, const enum e_token type)
{
	t_token	*li;

	li = malloc(sizeof(t_token));
	if (li)
	{
		li->content = content;
		li->token = type;
		li->next = NULL;
	}
	return (li);
}

/* gets the last token in the token list. Returns NULL if lst is NULL. */
t_token	*token_li_last(t_token *lst)
{
	if (lst)
	{
		while (lst->next)
		{
			lst = lst->next;
		}
	}
	return (lst);
}

/* pushes a token list item to the back of the token list */
void	token_li_push_back(t_token **lst, t_token *new)
{
	if (*lst)
	{
		token_li_last(*lst)->next = new;
	}
	else
	{
		*lst = new;
	}
}

/* frees a token list, including the content strings, and sets it to NULL. */
void	token_li_free(t_token **lst)
{
	t_token	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
}
