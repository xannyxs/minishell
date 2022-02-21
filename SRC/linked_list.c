/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   linked_list.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 16:15:22 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/18 14:57:43 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	lstsize(t_token	*head)
{
	int	n;

	n = 0;
	while (head)
	{
		n++;
		head = head->next;
	}
	return (n);
}

void	print_token(t_token *head)
{
	printf("\n");
	while (head != NULL)
	{
		printf("%d -> ", head->token);
		head = head->next;
	}
	printf("NULL\n");
	write(1, "\n", 1);
}

void	print_list(t_token *head)
{
	printf("\n");
	while (head != NULL)
	{
		printf("%s -> ", head->content);
		head = head->next;
	}
	printf("NULL\n");
	write(1, "\n", 1);
}

void	new_node(t_token **head, char *content, int token)
{
	t_token	*new_node;

	new_node = token_new(content, token);
	if (!new_node)
	{
		// TODO: error
		return ;
	}
	token_li_push_back(head, new_node);
}
