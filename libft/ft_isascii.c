/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isascii.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:52:56 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:52:57 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* checks if c is an ASCII character */
int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
