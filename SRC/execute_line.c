/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_line.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 17:44:20 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/09 13:47:58 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "function.h"
#include "ft_printf.h"

#include <unistd.h>
#include <stdlib.h>

static int	is_pipe_present(t_token *lst)
{
	while (lst)
	{
		if (lst->token == T_PIPE)
		{
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

//TODO: Error handeling
static int	execute_single_cmd(t_vars *vars)
{
	t_function	tf;
	char		**argv;
	t_token		*tlst;

	tlst = vars->token_list;
	argv = create_argv(&tlst);
	tf = get_function(*argv);
	if (tf.key != NULL)
	{
		vars->exit_code = (*tf.func)(argv, vars);
	}
	else
	{
		exec_command(argv, vars);
	}
	free(argv);
	return (vars->exit_code);
}

//TODO: Error handeling
// TODO: unify?
int	execute_line(t_vars *vars)
{
	if (is_pipe_present(vars->token_list))
		return (execute_multiple(vars));
	else
		return (execute_single_cmd(vars));
}
