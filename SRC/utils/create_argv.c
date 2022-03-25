/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_argv.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/11 16:15:34 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/24 21:24:25 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h> /* malloc */

/* creates a null-terminated argument string array.
 * should be freed. However, not the strings inside of them, as they are
 * borrowed from the token list.
 * Works only for simple commands without pipes or redirections. */
// TODO: not sure if this is the correct file to put this.
char	**create_argv(t_token *lst)
{
	size_t	size;
	size_t	i;
	char	**argv;

	size = token_lst_size(lst);
	argv = malloc((size + 1) * sizeof(char *));
	if (!argv)
		malloc_fail();
	i = 0;
	while (i < size)
	{
		argv[i] = lst->content;
		i++;
		lst = lst->next;
	}
	argv[i] = NULL;
	return (argv);
}

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
		*status |= -1;
		*status |= M_PS_EMPTY;
	}
}

/* creates a null-terminated string array of arguments(i.e. argv).
 * it increments the token list so that the next command starts after a
 * pipe. status is negative on failure; status is OR'd with M_PS_EMPTY
 * for when there is nothing to execute, or M_PS_REDIRECTION_FAILED when
 * a redirection is performed but failed. M_PS_REDIRECTED is set when
 * an redirection(succesfull or not) was performed. See also create_argv. */
char	**create_argv_advanced(t_token **lst, int *infd, int *outfd,
	int *status)
{
	size_t	size;
	size_t	i;
	char	**argv;

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

