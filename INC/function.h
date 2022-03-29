/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 12:25:24 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/29 18:58:30 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H
# include "minishell.h"

/* description:
key:	the name of the function. i.e. echo
func:	pointer to the builtin. char **argv, should be freed. But ONLY it,
		not the strings in there themselves, as they are simply reused
		from the token list in t_vars.
is_forkable:	1 if the function should run when forked, 0 when not. */
typedef struct s_function
{
	char	*key;
	int		(*func)(char **, t_vars *);
	char	is_forkable;
}	t_function;

t_function	get_function(const char *name);

void	m_proc(int infd, int outfd, char **args, t_vars *vars);

#endif
