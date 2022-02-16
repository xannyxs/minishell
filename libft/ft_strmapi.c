/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:54:01 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:54:02 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

/* TODO: double pass for more efficient mem alloc? */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dst;
	char			t;
	unsigned int	si;
	unsigned int	di;

	if (s == NULL || f == NULL)
		return (NULL);
	dst = malloc(ft_strlen(s) + 1);
	if (dst == NULL)
		return (dst);
	si = 0;
	di = 0;
	while (s[si] != 0)
	{
		t = f(si, s[si]);
		if (t)
		{
			dst[di] = t;
			di++;
		}
		si++;
	}
	dst[di] = 0;
	return (dst);
}
