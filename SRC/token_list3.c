/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_list3.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/09 13:15:11 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/10 18:20:22 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <unistd.h>

/* counts amount of elements until f(token) returns 1 */
size_t	token_count_upto(t_token *lst, int (*f)(t_token *))
{
	size_t	n;

	n = 0;
	while (lst)
	{
		if (f(lst))
			break ;
		n++;
		lst = lst->next;
	}
	return (n);
}

int	token_is_pipe(t_token *tok)
{
	return (tok->token == T_PIPE);
}

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