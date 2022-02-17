/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_char.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 15:16:34 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/17 17:08:53 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdbool.h>

int	check_redirect_stdout_append(char *prompt)
{
	if (prompt != NULL)
	{
		if (ft_strcmp(prompt, ">>") == 0)
			return (true);
	}
	return (false);
}

int	check_redirect_stdin(char *prompt)
{
	if (prompt != NULL)
	{
		if (ft_strcmp(prompt, "<") == 0)
			return (true);
	}
	return (false);
}

int	check_delimiter(char *prompt)
{
	if (prompt != NULL)
	{
		if (ft_strcmp(prompt, "<<") == 0)
			return (true);
	}
	return (false);
}

int	check_redirect_stdout(char *prompt)
{
	if (prompt != NULL)
	{
		if (ft_strcmp(prompt, ">") == 0)
			return (true);
	}
	return (false);
}

int	check_pipes(char *prompt)
{
	if (prompt != NULL)
	{
		if (ft_strcmp(prompt, "|") == 0)
			return (true);
	}
	return (false);
}
