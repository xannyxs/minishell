/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:53:15 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:53:16 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;
	void	*temp_content;

	new = NULL;
	while (lst)
	{
		temp_content = f(lst->content);
		if (temp_content)
		{
			temp = ft_lstnew(temp_content);
			if (temp == NULL)
			{
				ft_lstclear(&new, del);
				return (new);
			}
			ft_lstadd_back(&new, temp);
		}
		lst = lst->next;
	}
	return (new);
}
