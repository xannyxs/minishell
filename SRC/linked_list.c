/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   linked_list.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 16:15:22 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/22 11:00:22 by xvoorvaa      ########   odam.nl         */
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

void	print_list(t_envlist *head)
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

void	new_node_token(t_token **head, char *content, int token)
{
	t_token	*new_node;

	new_node = token_new(content, token);
	if (!new_node)
	{
		// TODO: Error management
		free(new_node);
		return ;
	}
	token_li_push_back(head, new_node);
}

void	new_node(t_envlist **head, char *variable, char *content)
{
	t_envlist	*new_node;
	t_envlist	*last_node;

	new_node = ft_calloc(sizeof(t_envlist), 1);
	if (!new_node)
	{
		// TODO: Error management
		free(new_node);
		return ;
	}
	last_node = *head;
	new_node->variable = variable;
	new_node->content = content;
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = new_node;
	}
}