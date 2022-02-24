/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 13:38:41 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/02/24 12:19:30 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//#include "libft.h" /* ft_putstr_fd */

#include <stdio.h> /* perror */
#include <stdlib.h> /* exit */

/*void	fatal_error(const char *msg, const int exit_code)
{
	ft_putstr_fd(msg, 2);
	exit(exit_code);
}*/

void	fatal_error(const char *msg, unsigned char err_number)
{
	errno = err_number;
	perror(msg);
	exit(err_number);
}
