/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_command.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 16:55:19 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/24 13:02:41 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define READ 0
#define WRITE 1

/*
	Needs some cleaning. Not my best code.
*/

static char	**allocate_input(t_vars *vars)
{
	int		i;
	int		j;
	char	**input;
	t_token	*temp;

	i = 0;
	temp = vars->token_list->next;
	while (temp != NULL && temp->token != T_PIPE)
	{
		temp = temp->next;
		i++;
	}
	temp = vars->token_list->next;
	input = malloc((i + 2) * sizeof(char *));
	input[0] = vars->token_list->content;
	j = i;
	i = 1;
	while (i <= j)
	{
		input[i] = temp->content;
		temp = temp->next;
		i++;
	}
	input[i] = NULL;
	return (input);
}

int	exec_command(t_vars *vars)
{
	pid_t	fork_id1;
	char	*usr_func;
	char	**input;

	fork_id1 = fork();
	if (fork_id1 == 0)
	{
		input = allocate_input(vars);
		usr_func = path_check(vars->token_list->content, \
			find_dir(vars->environ));
		if (usr_func == NULL || input == NULL)
			return (-1);
		execve(usr_func, input, vars->environ);
		fatal_error(vars->token_list->content);
		return (errno);
	}
	if (fork_id1 < 0)
		return (-1);
	waitpid(fork_id1, NULL, 0);
	return (0);
}
