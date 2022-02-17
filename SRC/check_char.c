/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_char.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 15:16:34 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/17 15:25:11 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>

//TODO: Change name of function
int	check_redirect(char **prompt)
{
	int	i;

	i = 0;
	while (prompt[i] != NULL)
	{
		if (ft_strcmp(prompt[i], ">") == 0)
			return (true);
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
