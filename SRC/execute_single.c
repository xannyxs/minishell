/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_single.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:55:19 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/22 15:11:53 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <unistd.h> /* execve */
#include <stdlib.h> /* exit */
#include <stdio.h> /* perror */

#include <sys/wait.h> /* wait */
#include <sys/types.h>
#include <termios.h>

static void	sighandler(int sig)
{
	write(STDOUT_FILENO, "\n", 1);
	(void) sig;
}

static void	deactivate_signals(void)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
}

/*
	The ft_split in this function is for the function export.
	See function_export.c for more info.
*/
int	exec_command(char **argv, t_vars *vars)
{
	pid_t	pid;
	char	*path;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signals();
		if (ft_strchr(argv[0], ' ') != NULL)
			argv = ft_split(argv[0], ' ');
		path = pathresolve_tryfind(*argv, vars->environ);
		if (!path)
			path = "";
		if (execve(path, argv, vars->environ) == -1)
		{
			perror(*argv);
			exit(126 + (errno == 2));
		}
	}
	else if (pid == -1)
		fatal_perror("fork");
	deactivate_signals();
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		vars->exit_code = WEXITSTATUS(status);
		// printf("%d\n", status);
		vars->exit_code = WIFEXITED(status);
		// printf("%d\n", status);
	signals();
	return (vars->exit_code);
}
