/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:53:56 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:53:57 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* strlcpy straight up stolen from myself, but this one doesn't
 * return the length, so we save an unnecessary strlen(src) operation.
 * Also doesn't check if dstsize == 0. Probably nitpicking. */
static void	m_strlcpy(char *dst, const char *src, const size_t dstsize)
{
	size_t	n;

	n = 0;
	while (n < dstsize - 1 && src[n] != 0)
	{
		dst[n] = src[n];
		n++;
	}
	dst[n] = 0;
}

/* Concats src to dst with a maximum of dstsize chars.
 * returns the length of the string it intended to create. */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;

	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	if (dstlen >= dstsize)
	{
		return (dstsize + srclen);
	}
	m_strlcpy((dst + dstlen), src, dstsize - dstlen);
	return (srclen + dstlen);
}
