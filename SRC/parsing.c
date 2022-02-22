/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 14:15:14 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/22 17:28:54 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	LET OP HET VOLGENDE:
	- Single quote: Neemt het letterlijk, voorbeeld: "echo '$PATH'" - Output: $PATH
	- Dubble quote: Doet normaal
	- Dollar Sign: Kijkt of het een variable is.
	- ENV
	- "<< >>" is different from "< >"
	- Be careful with minus (-)
*/

// this is temporary.
// TODO: expansion.
// TODO: merging of literals.
static int	parse(t_vars *vars)
{
	t_token	*cur;

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
	return (1);
}

int	init_vars(const char *line, t_vars *vars)
{
	vars->token_list = NULL;
	vars->var_list = NULL;
	lex(&vars->token_list, line);
	parse(vars);
	// print_list(parsing->token_list);
	// print_token(parsing->token_list);
	return (0);
}
