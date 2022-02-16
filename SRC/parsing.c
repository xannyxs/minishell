/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 14:15:14 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/16 15:49:51 by xvoorvaa      ########   odam.nl         */
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

int	access_command(char **prompt, t_parsing *parsing)
{
	int	i;
	int	err;

	i = 0;
	err = -1;
	while (prompt[i] != NULL)
	{
		err = access(F_OK)
		i++;
	}
	return (false);
}

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

int	start_parsing(char **prompt, t_parsing *parsing)
{
	int	i;

	i = 0;
	parsing->pipe_check = check_pipes(prompt);
	while (prompt[i] != NULL)
	{
		
	}
	return (0);
}
