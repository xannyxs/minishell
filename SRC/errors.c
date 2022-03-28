/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 13:38:41 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/28 18:10:40 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h> /* perror */
#include <stdlib.h> /* exit */

void	fatal_perror(const char *msg)
{
	perror(msg);
	exit(errno);
}

void	malloc_fail(void)
{
	fatal_perror("malloc");
}
