/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_heredoc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/22 14:59:23 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/04 17:02:30 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* ft_strncmp */
#include "ft_printf.h" /* ft_strncmp */
#include "get_next_line.h"

#include <unistd.h> /* pipe, fork, write, STDIN_FILENO */
#include <stdlib.h> /* exit */

#include <sys/wait.h> /* wait */

#include <signal.h> /* signal, kill */

static void	child(const char *limiter, const int writefd)
{
	char	*line;
	size_t	lim_len;
	ssize_t	r;

	lim_len = ft_strlen(limiter);
	while (true)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO, &r);
		if (line == NULL)
		{
			if (r == -1)
				fatal_perror("read");
			break ;
		}
		else if (ft_strncmp(line, limiter, lim_len) == 0
			&& line[lim_len] == '\n' && line[lim_len + 1] == 0)
			break ;
		r = write(writefd, line, r);
		free(line);
		if (r == -1)
			fatal_perror("write");
	}
	if (line != NULL)
		free(line);
}

static pid_t	heredoc_dofork(t_token *tok, int *pfds)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		fatal_perror("fork");
	else if (pid == 0)
	{
		signals_heredoc();
		close(pfds[0]);
		child(tok->next->content, pfds[1]);
		close(pfds[1]);
		exit(0);
	}
	return (pid);
}

void	redir_heredoc(t_token *tok, int *infd, int *status)
{
	int		status_child;
	int		exit_code;
	int		pfds[2];
	pid_t	pid;

	exit_code = 0;
	ft_close_fd(*infd);
	if (pipe(pfds) == -1)
		fatal_perror("pipe");
	signal(SIGUSR1, SIG_IGN);
	pid = heredoc_dofork(tok, pfds);
	deactivate_signals_heredoc();
	close(pfds[1]);
	*infd = pfds[0];
	*status |= M_PS_REDIRECTED_STDIN;
	waitpid(pid, &status_child, 0);
	if (WIFEXITED(status_child) == true)
		exit_code = WEXITSTATUS(status_child);
	if (exit_code != 0)
	{
		*status |= M_PS_HEREDOC_SIGINT;
		kill(0, SIGUSR1);
	}
	signal(SIGUSR1, SIG_DFL);
	signals_default();
}
