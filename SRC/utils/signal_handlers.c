/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handlers.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/22 20:47:34 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/29 15:59:15 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> /* rl_ extra lib */
#include <unistd.h> /* Write */
#include <readline/readline.h> /* rl_ functions */
#include <stdlib.h> /* exit */

void	sighandler_heredoc(int sig)
{
	write(STDOUT_FILENO, "\n", 1);
	exit(1);
	(void) sig;
}

void	sighandler_pipes_quit(int sig)
{
	printf("Quit: 3\n");
	(void) sig;
}

void	sighandler_pipes(int sig)
{
	printf("\n");
	(void) sig;
}

void	sighandler_default(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}
