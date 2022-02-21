/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 12:25:24 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/21 12:34:54 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H
# include "minishell.h"

typedef struct s_conversions
{
	char	*key;
	int		(*func)(t_vars);
}	t_conversions;

t_conversions	s_conversions[] = {
	{"echo", &exec_echo},
	{"cd", &exec_cd},
	{0, NULL}
};

#endif