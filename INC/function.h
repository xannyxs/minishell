/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 12:25:24 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/08 17:28:52 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H
# include "minishell.h"

typedef struct s_function
{
	char	*key;
	int		(*func)(t_vars *);
	char	is_forkable;
}	t_function;

#endif
