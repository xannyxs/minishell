/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtolower.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:54:20 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:54:21 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtolower(char *s)
{
	const char	*orig;

	orig = s;
	while (*s != 0)
	{
		if (*s >= 'A' && *s <= 'Z')
		{
			*s += ('a' - 'A');
		}
		s++;
	}
	return ((char *)orig);
}
