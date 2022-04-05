/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_is_valid_setarg.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 19:39:37 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/04/05 16:55:46 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" /* ft_isalnum etc. */

#include <stdbool.h> /* Bool */

bool	ft_is_valid_setarg(const char *arg)
{
	int	i;

	if (ft_isalpha(arg[0]) == false && arg[0] != '_')
		return (false);
	i = 0;
	while (arg[i] != '\0' && arg[i] != '=')
	{
		if (ft_isalnum(arg[i]) == false && arg[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	ft_is_valid_unsetarg(const char *arg)
{
	if (ft_isalpha(*arg) == false && *arg != '_')
	{
		return (false);
	}
	arg++;
	while (*arg)
	{
		if (!ft_isalnum(*arg) && *arg != '_')
			return (false);
		arg++;
	}
	return (true);
}
