/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:53:46 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:53:47 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* locates memory location of char c in s, returns NULL if not found. */
char	*ft_strchr(const char *s, int c)
{
	while (*s != 0)
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	if ((char)c == 0)
	{
		return ((char *)s);
	}
	return (NULL);
}
