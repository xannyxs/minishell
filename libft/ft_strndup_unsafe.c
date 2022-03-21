/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strndup_unsafe.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/17 18:13:12 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/17 18:25:54 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h> /* malloc */

/* this is a strdup which stops at len characters.]
 * it duplicates string s1 with len characters. Returns NULL on malloc fail.
 * it does NO BOUNDS CHECKING. If you give a len greater than its
 * string length, it will access memory it's not supposed to. */
char	*ft_strndup_unsafe(const char *s1, const size_t len)
{
	char	*s2;

	s2 = malloc((len + 1) * sizeof(char));
	if (s2 != NULL)
	{
		ft_memcpy(s2, s1, len);
		s2[len] = 0;
	}
	return (s2);
}
