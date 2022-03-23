/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/10 13:13:02 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/23 14:20:33 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"

#include <fcntl.h> /* open */
#include <stdio.h> /* perror */
#include <unistd.h> /* STD */

static void	m_check_error(t_token *tok, int fd, int *status)
{
	*status |= M_PS_REDIRECTED;
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: ");
		perror(tok->next->content);
		*status |= -1;
		*status |= M_PS_REDIRECTION_FAILED;
	}
}

/* Open changes ERRNO to 2 if it fails. Bash makes it 1, but we will keep it 2 :) */
static void	redir_in(t_token *tok, int *infd, int *status)
{
	ft_close_fd(*infd);
	*infd = open(tok->next->content, O_RDONLY);
	m_check_error(tok, *infd, status);
}

static void	redir_out(t_token *tok, int *outfd, int *status)
{
	int	opts;

	ft_close_fd(*outfd);
	opts = O_CREAT | O_WRONLY;
	if (tok->token == T_REDIRECT_STDOUT_TO_FILE_APPEND)
		opts |= O_APPEND;
	else
		opts |= O_TRUNC;
	*outfd = open(tok->next->content, opts, 0664);
	m_check_error(tok, *outfd, status);
}

// TODO: here_doc
void	do_redirect(t_token **tlst, int *infd, int *outfd, int *status)
{
	t_token	*tok;

	tok = *tlst;
	if ((*status & M_PS_REDIRECTION_FAILED) == 0)
	{
		if (tok->token == T_REDIRECT_FILE_TO_STDIN)
		{
			redir_in(tok, infd, status);
		}
		else if (tok->token == T_REDIRECT_STDOUT_TO_FILE
			|| tok->token == T_REDIRECT_STDOUT_TO_FILE_APPEND)
		{
			redir_out(tok, outfd, status);
		}
	}
	*tlst = tok->next->next;
}
