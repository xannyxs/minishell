/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_argv.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/11 16:15:34 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/06 13:32:35 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h> /* malloc */

static size_t	create_argv_advanced_count(t_token *lst)
{
	size_t	n;

	n = 0;
	while (lst)
	{
		if (lst->token == T_PIPE)
			break ;
		else if (token_is_redirect(lst))
		{
			lst = lst->next->next;
			continue ;
		}
		n++;
		lst = lst->next;
	}
	return (n);
}

/* damn you norm!!! */
static void	create_argv_adv_cleanup(t_token **lst, size_t size, int *status)
{
	if (*lst)
		*lst = (*lst)->next;
	if (size == 0)
	{
		*status |= get_negative_bit();
		*status |= M_PS_EMPTY;
	}
}

/* creates a null-terminated string array of arguments(i.e. argv).
 * it increments the token list so that the next command starts after a
 * pipe. status is negative(negative, *NOT* -1) on failure;
 * that is, that the current command should not be executed(i.e.
 * empty/redir failure). status is OR'd with M_PS_EMPTY for when there is
 * nothing to execute, or M_PS_REDIRECTION_FAILED when a redirection is
 * performed but failed. M_PS_REDIRECTED is set when an
 * redirection(succesfull or not) was performed. M_PS_HEREDOC_SIGINT is set
 * when the heredoc process received a SIGINT.
 * WARNING: return value must be freed, however * NOT * its contents,
 * as these are borrowed from the token list. */
char	**create_argv_advanced(t_token **lst, int *infd, int *outfd,
	int *status)
{
	size_t	size;
	size_t	i;
	char	**argv;

	*status = 0;
	size = create_argv_advanced_count(*lst);
	argv = malloc((size + 1) * sizeof(char *));
	if (!argv)
		malloc_fail();
	i = 0;
	while (*lst && (*lst)->token != T_PIPE)
	{
		if (token_is_redirect(*lst))
		{
			do_redirect(lst, infd, outfd, status);
			continue ;
		}
		argv[i] = (*lst)->content;
		*lst = (*lst)->next;
		i++;
	}
	argv[i] = NULL;
	create_argv_adv_cleanup(lst, size, status);
	return (argv);
}
