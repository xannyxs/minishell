/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 14:15:14 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/23 16:19:43 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* ft_strjoin */

#include <stdlib.h> /* free */
#include <stdbool.h>

#include <stdlib.h>

/*
	LET OP HET VOLGENDE:
	- Single quote: Neemt het letterlijk, voorbeeld: "echo '$PATH'" - Output: $PATH
	- Dubble quote: Doet normaal
	- Dollar Sign: Kijkt of het een variable is.
	- ENV
	- "<< >>" is different from "< >"
	- Be careful with minus (-)
*/

static void	expand_vars(t_vars *vars)
{
	t_token	*cur;
	
	cur = vars->token_list;
	while (cur)
	{
		if (cur->token == T_LITERAL_EXPANDING)
		{
			expand_token(cur, vars);
			cur->token = T_LITERAL;
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
			// TODO: error
		}
		token_free(next);
		lst->content = new_content;
		return (true);
	}
	return (false);
}

// this is temporary.
// TODO: expansion.
/* basic process:
 * 1: expand the literals that need expansion
 * 2: boil all literals down to just T_LITERAL.
 * 3: merge literals that are together.
 * 4: done. */
static int	parse(t_vars *vars)
{
	t_token	*cur;

	expand_vars(vars);
	cur = vars->token_list;
	while (cur)
	{
		if (cur->token == T_LITERAL_EXPANDING
			|| cur->token == T_LITERAL_NONEXPANDING)
		{
			cur->token = T_LITERAL;
		}
		cur = cur->next;
	}
	cur = vars->token_list;
	while (cur)
	{
		if (!try_merge(cur))
		{
			cur = cur->next;
		}
	}
	return (1);
}

int	init_vars(const char *line, t_vars *vars)
{
	vars->token_list = NULL;
	vars->var_list = NULL;
	lex(&vars->token_list, line);
	if (vars->token_list == NULL)
		exit (ENOMEM);
	parse(vars);
	// print_list(parsing->token_list);
	// print_token(parsing->token_list);
	return (0);
}
