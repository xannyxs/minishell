/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_list2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 13:22:17 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/02/25 13:54:30 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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
