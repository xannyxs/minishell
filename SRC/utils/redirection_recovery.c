/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection_recovery.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 17:19:50 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/25 19:24:17 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h> /* dup, close */

/* restores stdin/stdout if redirections were made. */
void	rr_restore_redirs(int *fds, int *old_fds, int status)
{
	if (old_fds[0] != -1)
	{
		if (status & M_PS_REDIRECTED_STDIN)
		{
			if (fds[0] != -1)
				close(0);
		}
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

/* checks if there are redirections in this simple(no pipe) command.
 * if there are, it creates a backup file descriptor for restoration.
 * we skip STDIN as there is no builtins using STDIN. */
void	rr_check_redirections(t_vars *vars, int *old_fds)
{
	t_token	*lst;

	old_fds[0] = -1;
	old_fds[1] = -1;
	lst = vars->token_list;
	while (lst)
	{
		if (lst->token == T_REDIRECT_STDOUT_TO_FILE
			|| lst->token == T_REDIRECT_STDOUT_TO_FILE_APPEND)
		{
			old_fds[1] = dup(1);
			if (old_fds[1] == -1)
			{
				fatal_perror("stdout backup dup");
			}
			break ;
		}
		lst = lst->next;
	}
}
