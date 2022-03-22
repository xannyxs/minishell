/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/15 14:05:01 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/22 21:37:59 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"

#include <unistd.h>
#include <signal.h>
#include <termios.h>

/*
	The function "Signal()" will change some settings
	of the shell. signal(SIGINT, sighandler) will redirect CTRL + C.

	signal(SIGQUIT, SIG_IGN) will ignore CTRL + |.
*/

void	deactivate_signals(void)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	signal(SIGINT, sighandler_pipes);
	signal(SIGQUIT, sighandler_pipes_quit);
}

void	signals_child(void)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	signal(SIGINT, sighandler_pipes);
	signal(SIGQUIT, sighandler_default);
}
void	signals(void)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	signal(SIGINT, sighandler_default);
	signal(SIGQUIT, SIG_IGN);
}
