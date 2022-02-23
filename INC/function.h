/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 12:25:24 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/22 16:53:47 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H
# include "minishell.h"

typedef struct s_function
{
	char	*key;
	int		(*func)(t_vars *);
}	t_function;

#endif
