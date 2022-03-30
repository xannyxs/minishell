/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handlers.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/22 20:47:34 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/30 15:01:08 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <stdlib.h>

void	sighandler_heredoc(int sig)
{
	ft_printf("\n");
	exit(1);
	(void) sig;
}

void	sighandler_pipes_quit(int sig)
{
	ft_printf("Quit: 3\n");
	(void) sig;
}

void	sighandler_pipes(int sig)
{
	ft_printf("\n");
	(void) sig;
}

void	sighandler_default(int sig)
{
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}
