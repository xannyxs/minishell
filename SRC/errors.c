/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 13:38:41 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/22 14:52:00 by jobvan-d      ########   odam.nl         */
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

void	malloc_fail()
{
	fatal_perror("malloc");
}
