/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:52:55 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:52:56 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* checks if c is an alphabetical char */
int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
