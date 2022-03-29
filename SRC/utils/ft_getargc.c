/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_getargc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/15 17:54:59 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/29 15:56:43 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h> /* NULL */

int	ft_getargc(char *argv[])
{
	int	argc;

	argc = 0;
	while (argv[argc] != NULL)
		argc++;
	return (argc);
}
