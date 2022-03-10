/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/10 13:13:02 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/10 22:12:34 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <fcntl.h> /* open */
#include <stdio.h> /* perror */

// TODO: what on failure?

static void	redir_in(t_token *tok, int *infd)
{
	ft_close_fd(*infd);
	*infd = open(tok->next->content, O_RDONLY);
	if (*infd == -1)
	{
		perror(tok->next->content);
	}
}

// TODO: add minishell: to error
static void	redir_out(t_token *tok, int *outfd)
{
	int	opts;

	ft_close_fd(*outfd);
	opts = O_CREAT | O_WRONLY;
	if (tok->token == T_REDIRECT_STDOUT_TO_FILE_APPEND)
		opts |= O_APPEND;
	else
		opts |= O_TRUNC;
	*outfd = open(tok->next->content, opts, 0664);
	if (*outfd == -1)
	{
		perror(tok->next->content);
	}
}

// TODO: here_doc
void	do_redirect(t_token **tlst, int *infd, int *outfd, int *outfdchanged)
{
	t_token	*tok;

	tok = *tlst;
	if (tok->token == T_REDIRECT_FILE_TO_STDIN)
	{
		redir_in(tok, infd);
	}
	else if (tok->token == T_REDIRECT_STDOUT_TO_FILE
		|| tok->token == T_REDIRECT_STDOUT_TO_FILE_APPEND)
	{
		*outfdchanged = 1;
		redir_out(tok, outfd);
	}
	*tlst = tok->next->next;
}
