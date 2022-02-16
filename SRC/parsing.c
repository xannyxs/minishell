/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 14:15:14 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/16 16:24:26 by xvoorvaa      ########   odam.nl         */
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

int	check_pipes(char **prompt)
{
	int	i;

	i = 0;
	while (prompt[i] != NULL)
	{
		if (ft_strcmp(prompt[i], "|") == 0)
			return (true);
		i++;
	}
	return (false);
}

int	init_parsing(t_parsing *parsing)
{
	int	i;

	i = 0;
	parsing->pipe_check = check_pipes(parsing->prompt);
	while (parsing->prompt[i] != NULL)
	{
		new_node(&parsing->tokenizer, parsing->prompt[i]);
		i++;
	}
	print_list(parsing->tokenizer);
	return (0);
}
