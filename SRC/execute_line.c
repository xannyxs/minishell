/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_line.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 17:44:20 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/04/06 14:13:13 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "function.h" /* TF struct */

#include <stdlib.h> /* free */

static int	is_pipe(const t_token *tok)
{
	return (tok->token == T_PIPE);
}

/* For simple commands(no piping), returns the t_function entry for
 * the built in. If it's not found, it's filled with zeroes. */
static t_function	get_builtin(t_token *tlst)
{
	const t_function	empty = {0, NULL, 0};

	while (tlst)
	{
		if (tlst->token == T_LITERAL)
		{
			return (get_function(tlst->content));
		}
		else if (token_is_redirect(tlst))
		{
			tlst = tlst->next;
		}
		tlst = tlst->next;
	}
	return (empty);
}

static int	m_run_builtin(t_vars *vars, t_token *tlst, t_function tf)
{
	char	**argv;
	int		fds[2];
	int		old_fds[2];
	int		status;

	fds[0] = -1;
	fds[1] = 1;
	rr_check_redirections(vars, old_fds);
	argv = create_argv_advanced(&tlst, fds, fds + 1, &status);
	vars->exit_code = (*tf.func)(argv, vars);
	if (vars->exit_code == 0 && status < 0)
	{
		vars->exit_code = 1;
	}
	free(argv);
	rr_restore_redirs(fds, old_fds, status);
	return (status);
}

//TODO: Error handeling
// perhaps check if thing is a builtin or not.
// then branch cuz easier.
// slightly cursed tho. but we have to, because a builtin does not fork,
// so we'll have to redirect and restore stdout.
// this is not necessary for the normal execution, because that is forked.
/* a single cmd is when there are no pipes, but there may be redirection
 * present. */
static int	execute_single_cmd(t_vars *vars)
{
	t_function	tf;

	tf = get_builtin(vars->token_list);
	if (tf.key != NULL)
	{
		m_run_builtin(vars, vars->token_list, tf);
	}
	else
	{
		vars->exit_code = execute_multiple(vars);
	}
	return (vars->exit_code);
}

//TODO: Error handeling
int	execute_line(t_vars *vars)
{
	if (token_get_first_occurrence(vars->token_list, &is_pipe) != NULL)
		return (execute_multiple(vars));
	else
		return (execute_single_cmd(vars));
}
