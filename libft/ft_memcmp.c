/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:53:27 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:53:28 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 1;
	while (i < n)
	{
		if (*((const unsigned char *)s1) != *((const unsigned char *)s2))
			break ;
		s1++;
		s2++;
		i++;
	}
	return (*((const unsigned char *)s1) - *((const unsigned char *)s2));
}
