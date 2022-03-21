/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putchar_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:53:34 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:53:35 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <unistd.h>

void	ft_putchar_fd(const char c, int fd)
{
	write(fd, &c, 1);
}
