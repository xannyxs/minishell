/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_list3.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/09 13:15:11 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/11 15:52:30 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	token_lst_size(t_token *lst)
{
	size_t	n;

	n = 0;
	while (lst)
	{
		n++;
		lst = lst->next;
	}
	return (n);
}

/* returns 1 if token is a type of redirect. */
int	token_is_redirect(const t_token *tok)
{
	return (tok->token == T_REDIRECT_FILE_TO_STDIN
		|| tok->token == T_REDIRECT_STDOUT_TO_FILE
		|| tok->token == T_REDIRECT_STDOUT_TO_FILE_APPEND
		|| tok->token == T_HEREDOC);
}
