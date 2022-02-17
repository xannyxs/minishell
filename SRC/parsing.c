/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 14:15:14 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/17 16:01:48 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

/*
	LET OP HET VOLGENDE:
	- Single quote: Neemt het letterlijk, voorbeeld: "echo '$PATH'" - Output: $PATH
	- Dubble quote: Doet normaal
	- Dollar Sign: Kijkt of het een variable is.
	- ENV
	- "<< >>" is different from "< >"
	- Be careful with minus (-)
*/

int	init_parsing(t_parsing *parsing)
{
	int	i;

	i = 0;
	while (parsing->prompt[i] != NULL)
	{
		if (check_pipes(parsing->prompt) == true)
			new_node(&parsing->token_list, parsing->prompt[i], T_PIPE);
		else if (check_redirect(parsing->prompt) == true)
			new_node(&parsing->token_list, parsing->prompt[i], T_REDIRECT_STDOUT_TO_FILE);
		else
			new_node(&parsing->token_list, parsing->prompt[i], T_LITERAL);
		i++;
	}
	print_list(parsing->token_list);
	print_token(parsing->token_list);
	return (0);
}
