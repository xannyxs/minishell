/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_valued_chars.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 19:39:37 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/29 15:57:02 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdbool.h> /* Bool */

bool	ft_valued_chars(char *argv)
{
	int	i;

	if (ft_isalpha(argv[0]) == false && argv[0] != '_')
		return (false);
	i = 0;
	while (argv[i] != '\0' && argv[i] != '=')
	{
		if (ft_isalnum(argv[i]) == false && argv[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
