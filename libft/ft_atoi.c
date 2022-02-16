/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:52:04 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/02/03 15:49:53 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* gets the offset of where there is no longer whitespace in string s */
static unsigned int	m_get_space_offset(const char *s)
{
	unsigned int	n;

	n = 0;
	while (ft_isspace(s[n]))
	{
		n++;
	}
	return (n);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	flip_sign_at_end;

	res = 0;
	flip_sign_at_end = -1;
	str += m_get_space_offset(str);
	if (*str == '-')
	{
		str++;
		flip_sign_at_end = 1;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res -= *str - '0';
		str++;
	}
	return (res * flip_sign_at_end);
}
