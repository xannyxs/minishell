/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 14:15:14 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/19 14:17:30 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* ft_strjoin */

#include <stdlib.h> /* free */
#include <stdbool.h>
#include <stdio.h>

static void	expand_vars(t_vars *vars)
{
	t_token	*cur;
	t_token	*next;

	cur = vars->token_list;
	while (cur)
	{
		if (cur->token == T_LITERAL || cur->token == T_LITERAL_QUOTED)
		{
			expand_token(cur, vars);
			if (cur->token == T_LITERAL && *cur->content == 0)
			{
				next = cur->next;
				token_remove_from_list(&vars->token_list, cur);
				cur = next;
				continue ;
			}
		}
		cur = cur->next;
	}
}

/* checks if the current and next token needs merging.
 * returns true if it has done a merge, else false. */
static int	try_merge(t_token *lst)
{
	t_token	*next;
	char	*new_content;

	next = lst->next;
	if (next && lst->token == T_LITERAL && next->token == T_LITERAL
		&& !next->separated_from_previous)
	{
		lst->next = next->next;
		new_content = ft_strjoin(lst->content, next->content);
		free(lst->content);
		if (!new_content)
		{
			fatal_perror("malloc");
		}
		token_free(next);
		lst->content = new_content;
		return (true);
	}
	return (false);
}

/* basic process:
 * 1: expand the literals that need expansion
 * 2: boil all literals down to just T_LITERAL.
 * 3: merge literals that are together.
 * 4: make list doubly linked.
 * 5: done. */
static int	parse(t_vars *vars)
{
	t_token	*cur;

	expand_vars(vars);
	cur = vars->token_list;
	while (cur)
	{
		if (cur->token == T_LITERAL_NONEXPANDING
			|| cur->token == T_LITERAL_QUOTED)
		{
			cur->token = T_LITERAL;
		}
		cur = cur->next;
	}
	cur = vars->token_list;
	while (cur)
	{
		if (!try_merge(cur))
			cur = cur->next;
	}
	token_make_list_doubly_linked(vars->token_list);
	return (1);
}

int	init_vars(const char *line, t_vars *vars)
{
	vars->token_list = NULL;
	if (lex(&vars->token_list, line) == -1)
		return (-1);
	parse(vars);
	if (!lex_validate(vars->token_list))
		return (-1);
	// print_list(parsing->token_list);
	// print_token(parsing->token_list);
	return (0);
}
