/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:53:50 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:53:51 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h> /* malloc */

/* duplicates s1 and returns it. Returns NULL on malloc failure. */
char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	len;

	len = ft_strlen(s1) + 1;
	s2 = malloc(len);
	if (s2 == NULL)
		return (s2);
	ft_memcpy(s2, s1, len);
	return (s2);
}
