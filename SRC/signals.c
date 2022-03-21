/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/15 14:05:01 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/21 17:32:15 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <signal.h>
#include <stdio.h> /* NEEDED FOR READLINE LIB */
#include <readline/readline.h>
#include <termios.h>

/*
	The function "Signal()" will change some settings
	of the shell. signal(SIGINT, sighandler) will redirect CTRL + C.

	signal(SIGQUIT, SIG_IGN) will ignore CTRL + |.
*/

static void	sighandler(int sig)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

void	signals(void)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
}