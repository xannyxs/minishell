/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_list3.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/09 13:15:11 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/11 16:05:19 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <unistd.h>

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

// TODO: Remove in final 
void	print_token(t_token *head)
{
	printf("\n");
	while (head != NULL)
	{
		printf("%s(%s, %d) -> ", head->content, head->separated_from_previous ? "sep" : "nosep",
			head->token);
		//printf("%s(%d) -> ", head->content, head->token);
		head = head->next;
	}
	printf("NULL\n");
	write(1, "\n", 1);
}
