/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 12:25:24 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/11 15:54:03 by jobvan-d      ########   odam.nl         */
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

/* returns a t_function entry if it's found, struct filled with zeroes
 * when not. */
t_function	get_function(const char *name);

char		**create_argv(t_token *lst);

char		**create_argv_advanced(t_token **lst, int *infd, int *outfd,
				int *status);

#endif
