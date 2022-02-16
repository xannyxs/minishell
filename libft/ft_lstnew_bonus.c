/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:53:18 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:53:19 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h> /* malloc, free */

t_list	*ft_lstnew(void *content)
{
	t_list	*li;

	li = malloc(sizeof(t_list));
	if (li == NULL)
	{
		return (li);
	}
	li->content = content;
	li->next = NULL;
	return (li);
}
