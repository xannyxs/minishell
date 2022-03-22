/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handlers.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/22 20:47:34 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/22 21:38:15 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>

void	sighandler_pipes_quit(int sig)
{
	ft_dprintf(STDOUT_FILENO, "Quit: 3\n");
	(void) sig;
}

void	sighandler_pipes(int sig)
{
	ft_dprintf(STDOUT_FILENO, "\n");
	(void) sig;
}

void	sighandler_default(int sig)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}