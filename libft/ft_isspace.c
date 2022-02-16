/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isspace.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 15:49:40 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/02/03 16:04:37 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* checks if c is a whitespace character.
 * `switch' would have been perfect here xD */
int	ft_isspace(const int c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}
