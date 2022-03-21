/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:54:00 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:54:01 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* intead of doing the classic integer counting,
 * increment the pointer. this is slightly faster
 * (probably has to do something with memory access or something idk) */
size_t	ft_strlen(const char *s)
{
	const char	*start;

	start = s;
	while (*s != 0)
	{
		s++;
	}
	return (s - start);
}
