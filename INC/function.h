/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 12:25:24 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/21 22:19:32 by xander        ########   odam.nl         */
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

t_function	g_function[] = {
{"echo", &exec_echo},
{"cd", &exec_cd},
{"pwd", &exec_pwd},
{"export", &exec_export},
//{"unset", &exec_unset},
{"env", &exec_env},
//{"exit", &exec_exit},
{0, NULL}
};

#endif
