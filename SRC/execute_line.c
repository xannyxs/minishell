/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_line.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 17:44:20 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/25 17:35:15 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "function.h"
#include "ft_printf.h"

#include <stdlib.h>


#include <unistd.h>


static int	is_pipe(const t_token *tok)
{
	return (tok->token == T_PIPE);
}

/* checks if there are redirections in this simple(no pipe) command.
 * if there are, it creates a backup file descriptor for restoration.
 * in theory, we don't have to */
void	rr_check_redirections(t_vars *vars, int *old_fds)
{
	t_token	*lst;

	old_fds[0] = -1;
	old_fds[1] = -1;
	lst = vars->token_list;
	while (lst)
	{
		if (lst->token == T_HEREDOC
			|| lst->token == T_REDIRECT_FILE_TO_STDIN)
		{
			old_fds[0] = dup(0);
			if (old_fds[0] == -1)
				fatal_perror("stdin backup dup");
			lst = lst->next;
		}
		else if (lst->token == T_REDIRECT_STDOUT_TO_FILE
			|| lst->token == T_REDIRECT_STDOUT_TO_FILE_APPEND)
		{
			old_fds[1] = dup(1);
			if (old_fds[1] == -1)
				fatal_perror("stdout backup dup");
			lst = lst->next;
		}
		lst = lst->next;
	}
}

/* For simple commands(no piping), returns the t_function entry for
 * the built in. If it's not found, it's filled with zeroes. */
static t_function	get_builtin(t_token *tlst)
{
	const t_function	empty = { 0, NULL, 0 };

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

/* restores stdin/stdout if redirections were made. */
void	rr_restore_redirs(int *fds, int *old_fds, int status)
{
	if (old_fds[0] != -1)
	{
		if (status & M_PS_REDIRECTED_STDIN)
		{
			if (fds[0] != -1)
				close(0);
			if (dup(old_fds[0]) == -1)
				fatal_perror("dup stdin restore redir");
		}
		close(old_fds[0]);
	}
	if (old_fds[1] != -1)
	{
		if (status & M_PS_REDIRECTED_STDOUT)
		{
			if (fds[1] != -1)
				close(1);
			if (dup(old_fds[1]) == -1)
				fatal_perror("dup stdout restore redir");
		}
		close(old_fds[1]);
	}
}

static int	m_run_builtin(t_vars *vars, t_token *tlst, t_function tf)
{
	char	**argv;
	int		fds[2];
	int		old_fds[2];
	int		status;

	fds[0] = 0;
	fds[1] = 1;
	rr_check_redirections(vars, old_fds);
	argv = create_argv_advanced(&tlst, fds, fds + 1, &status);
	vars->exit_code = (*tf.func)(argv, vars);
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
// TODO: unify?
int	execute_line(t_vars *vars)
{
	if (token_get_first_occurrence(vars->token_list, &is_pipe) != NULL)
		return (execute_multiple(vars));
	else
		return (execute_single_cmd(vars));
}
