/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 14:15:14 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/29 16:14:08 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* ft_strjoin */

#include <stdlib.h> /* free */
#include <stdbool.h>

/* expands the variables, i.e. $USER becomes jobvan-d */
static void	expand_vars(t_vars *vars)
{
	t_token	*lst;

	lst = vars->token_list;
	while (lst)
	{
		if (lst->token == T_LITERAL || lst->token == T_LITERAL_QUOTED)
		{
			expand_token(lst, vars);
		}
		lst = lst->next;
	}
}

/* removes unqouted empty literals from empty/whitespace variables. */
static void	remove_empty_literals(t_vars *vars)
{
	t_token	**tracer;
	t_token	*to_remove;

	tracer = &vars->token_list;
	while (*tracer)
	{
		if ((*tracer)->token == T_LITERAL && *((*tracer)->content) == 0)
		{
			to_remove = *tracer;
			*tracer = to_remove->next;
			if (*tracer)
			{
				(*tracer)->separated_from_previous
					= to_remove->separated_from_previous;
			}
			token_free(to_remove);
			continue ;
		}
		tracer = &((*tracer)->next);
	}
}

/* checks if the current and next token needs merging.
 * returns true if it has done a merge, else false. */
static bool	try_merge(t_token *lst)
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
			malloc_fail();
		token_free(next);
		lst->content = new_content;
		return (true);
	}
	return (false);
}

/* basic process:
 * 1: expand the literals that need expansion
 * 2: because of bash weirdness, split T_LITERALs with spaces into separate
 *    args. Ex. l$TEST where $TEST="s -ltra" should work(but not l"$TEST")
 * 3: boil all literals down to just T_LITERAL.
 * 4: merge literals that are together.
 * 5: make list doubly linked.
 * 6: done. */
static int	parse(t_vars *vars)
{
	t_token	*cur;

	expand_vars(vars);
	split_literals_with_spaces(vars);
	remove_empty_literals(vars);
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
