/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   linked_list.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 16:15:22 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/17 16:42:52 by xvoorvaa      ########   odam.nl         */
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
	t_token	*last_token;

	new_node = ft_calloc(sizeof(t_token), 1);
	if (!new_node)
	{
		free(new_node);
		return ;
	}
	last_token = *head;
	new_node->content = content;
	new_node->token = token;
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		while (last_token->next != NULL)
			last_token = last_token->next;
		last_token->next = new_node;
	}
}
