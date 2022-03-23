/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_heredoc.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/22 14:59:23 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/23 13:49:41 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* ft_strncmp */
#include "get_next_line.h"

#include <unistd.h> /* pipe, fork, STDIN_FILENO */
#include <stdlib.h> /* exit */

#include <sys/wait.h> /* wait */
#include <sys/types.h>

static void	child(const char *limiter, const int writefd)
{
	char	*line;
	size_t	lim_len;
	ssize_t	r;

	lim_len = ft_strlen(limiter);
	while (1)
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

// TODO: signaling
// TODO: should heredoc fail be handled?
void	redir_heredoc(t_token *tok, int *infd)
{
	int		pfds[2];
	pid_t	pid;

	ft_close_fd(*infd);
	if (pipe(pfds) == -1)
		fatal_perror("pipe");
	pid = fork();
	if (pid == -1)
		fatal_perror("fork");
	else if (pid == 0)
	{
		close(pfds[0]);
		child(tok->next->content, pfds[1]);
		close(pfds[1]);
		exit(0);
	}
	close(pfds[1]);
	*infd = pfds[0];
	waitpid(pid, NULL, 0);
}
