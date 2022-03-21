/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalnum.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:52:53 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:52:54 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include  "libft.h"

/* checks if c is an alphabetical char or digits */
int	ft_isalnum(int c)
{
	return ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'));
}
