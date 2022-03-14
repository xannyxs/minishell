/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isprint.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:53:00 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:53:01 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* checks if c is a printable ASCII character.
 * starts from space, ends in delete. */
int	ft_isprint(int c)
{
	return (c >= 0x20 && c <= '~');
}
