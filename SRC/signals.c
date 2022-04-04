/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/15 14:05:01 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/04/04 14:34:30 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h> /* STDs */
#include <signal.h> /* signals */
#include <termios.h> /* tcsetattr */

/*
	The function "Signal()" will change some settings
	of the shell. signal(SIGINT, sighandler) will redirect CTRL + C.

	signal(SIGQUIT, SIG_IGN) will ignore CTRL + |.
*/

void	deactivate_signals_heredoc(void)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	deactivate_signals_pipes(void)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	signal(SIGINT, sighandler_pipes);
	signal(SIGQUIT, sighandler_pipes_quit);
}

void	signals_pipe(void)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	signal(SIGINT, sighandler_pipes);
	signal(SIGQUIT, sighandler_default);
	signal(SIGUSR1, sighandler_usr);
}

void	signals_heredoc(void)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	signal(SIGINT, sighandler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_default(void)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	signal(SIGINT, sighandler_default);
	signal(SIGQUIT, SIG_IGN);
}
