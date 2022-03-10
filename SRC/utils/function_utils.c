/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/09 12:42:49 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/10 22:15:56 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "function.h"
#include "libft.h" /* ft_strcmp */

#include <stdlib.h> /* malloc */

/* creates a null-terminated argument string array.
 * should be freed. However, not the strings inside of them, as they are
 * borrowed from the token list. */
// TODO: Works only for simple commands without redirections.
// TODO: not sure if this is the correct file to put this.
char	**create_argv(t_token **lst)
{
	size_t	size;
	size_t	i;
	char	**argv;

	size = token_count_upto(*lst, &token_is_pipe);
	argv = malloc((size + 1) * sizeof(char *));
	if (!argv)
		fatal_perror("malloc");
	i = 0;
	while (i < size)
	{
		argv[i] = (*lst)->content;
		i++;
		*lst = (*lst)->next;
	}
	if (*lst)
	{
		*lst = (*lst)->next;
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

// TODO: something < file | cat should work.
char	**create_argv_advanced(t_token **lst, int *infd, int *outfd,
	int *outfdchanged)
{
	size_t	size;
	size_t	i;
	char	**argv;

	size = create_argv_advanced_count(*lst);
	argv = malloc((size + 1) * sizeof(char *));
	if (!argv)
		fatal_perror("malloc");
	i = 0;
	while (*lst && (*lst)->token != T_PIPE)
	{
		if (token_is_redirect(*lst))
		{
			do_redirect(lst, infd, outfd, outfdchanged);
			continue ;
		}
		argv[i] = (*lst)->content;
		*lst = (*lst)->next;
		i++;
	}
	if (*lst)
	{
		*lst = (*lst)->next;
	}
	argv[i] = NULL;
	return (argv);
}

t_function	get_function(const char *name)
{
	const t_function	funcs[] = {
	{"echo", &exec_echo, 1},
	{"cd", &exec_cd, 0},
	{"pwd", &exec_pwd, 1},
	{"export", &exec_export, 0},
	{"unset", &exec_unset, 0},
	{"env", &exec_env, 1},
	{"exit", &exec_exit, 0},
	{0, NULL, 0}
	};
	int					i;

	i = 0;
	while (funcs[i].key != NULL)
	{
		if (ft_strcmp(funcs[i].key, name) == 0)
		{
			return (funcs[i]);
		}
		i++;
	}
	return (funcs[i]);
}
