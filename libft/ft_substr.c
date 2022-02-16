/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:54:23 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:54:24 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h> /* for malloc() */

/* this function does strlen every time. This is inefficient, but it will
 * detect if len is too big for the string. */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	n;
	size_t	s_len;
	char	*ret;

	if (s == NULL)
		return ((char *)s);
	n = 0;
	while (s[n] != 0 && n != start)
		n++;
	if (s[n] == 0)
		len = 0;
	else
	{
		s_len = ft_strlen(s) - start;
		if (s_len < len)
			len = s_len;
	}
	ret = malloc(len + 1);
	if (ret == NULL)
		return (ret);
	ft_memcpy(ret, s + n, len);
	ret[len] = 0;
	return (ret);
}
