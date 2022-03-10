/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   linked_list.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 16:15:22 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/10 16:36:57 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

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
