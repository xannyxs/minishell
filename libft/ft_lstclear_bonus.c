/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:53:08 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:53:09 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h> /* free */

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
}
