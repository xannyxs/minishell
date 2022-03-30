/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envlist_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 16:15:22 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/30 15:38:10 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	new_node(t_envlist **head, char *variable, char *content)
{
	t_envlist	*new_node;
	t_envlist	*last_node;

	new_node = ft_calloc(sizeof(t_envlist), 1);
	if (!new_node)
		malloc_fail();
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
