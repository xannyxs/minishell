/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:53:40 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:53:41 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <unistd.h> /* write */

#define MAX_INT_STRING_LEN (12)

/* CURSED IMPLEMENTATION: I don't want to write the same code twice,
 * but I cannot use malloc for putnbr, so I came up with a struct
 * instead. Note: length does NOT include null terminator('\0'). */
typedef struct s_itoa_str
{
	char		data[MAX_INT_STRING_LEN];
	int			length;
}				t_itoa_str;

static void	m_inverse_string(char *s, int len)
{
	int		i;
	int		j;
	char	t;

	i = 0;
	j = len - 1;
	while (i < j)
	{
		t = s[i];
		s[i] = s[j];
		s[j] = t;
		i++;
		j--;
	}
}

static int	m_itoa_set_data(int n, t_itoa_str *t, int *is_negative)
{
	int	i;

	i = 0;
	*is_negative = 0;
	if (n == 0)
	{
		t->data[i] = '0';
		i++;
	}
	else if (n < 0)
	{
		*is_negative = 1;
		t->data[i] = -(n % -10) + '0';
		n /= -10;
		i++;
	}
	while (n > 0)
	{
		t->data[i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	return (i);
}

static t_itoa_str	m_itoa(int n)
{
	t_itoa_str	t;
	int			i;
	int			is_negative;

	i = m_itoa_set_data(n, &t, &is_negative);
	if (is_negative)
	{
		t.data[i] = '-';
		i++;
	}
	t.data[i] = 0;
	m_inverse_string((char *)&t.data, i);
	t.length = i;
	return (t);
}

/* prints n to file descriptor fd.
 * a recursive approach could've worked, however, I like this approach more
 * as it uses one write call instead of multiple for larger numbers. */
void	ft_putnbr_fd(int n, int fd)
{
	t_itoa_str	t;

	t = m_itoa(n);
	write(fd, (char *)&t.data, t.length);
}

#undef MAX_INT_STRING_LEN
