/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cisupper.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:52:39 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:52:40 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_cisupper(const int c)
{
	return ((const unsigned char)c >= 'A'
		&& (const unsigned char)c <= 'Z');
}
