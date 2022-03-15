/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/15 14:05:01 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/15 14:11:49 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>

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
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
}