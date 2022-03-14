/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtoupper.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:54:21 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:54:22 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtoupper(char *s)
{
	const char	*orig;

	orig = s;
	while (*s != 0)
	{
		if (*s >= 'a' && *s <= 'z')
		{
			*s -= ('a' - 'A');
		}
		s++;
	}
	return ((char *)orig);
}
