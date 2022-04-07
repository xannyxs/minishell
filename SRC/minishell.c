/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 18:11:55 by xander        #+#    #+#                 */
/*   Updated: 2022/04/07 13:25:09 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h> /* free */
#include <stdio.h> /* FILE(required for readline) */
#include <readline/readline.h> /* Readline */
#include <readline/history.h> /* add_history */

/* this is the string for the prompt. the \001 and \002 are to specifiy the
 * begin and end of characters to ignore in width calculation
 * (they are for colours). The reason why the variable name is so short is
 * because of norm. */
#define P_STR ("\001\e[1;36m\002minishell \001\e[0;32m\002$> \001\e[0m\002")

static void	init_base_vars(t_vars *vars)
{
	vars->token_list = NULL;
	vars->var_list = NULL;
	vars->old_pwd = NULL;
	vars->pwd = NULL;
	vars->exit_code = 0;
}

/*
	Readline will wait for the user for an input.
	When the user writes to the STDIN. Our shell will
	use an lexer, pars, tokenize it and ofcourse execute it.
*/
static void	prompt_shell(t_vars *vars)
{
	int		err;
	char	*line;

	while (true)
	{
		line = readline(P_STR);
		add_history(line);
		if (!line)
			exit(vars->exit_code);
		else if (*line != 0)
		{
			err = init_vars(line, vars);
			free(line);
			if (err != 0)
			{
				token_free_list(&vars->token_list);
				continue ;
			}
			if (vars->token_list != NULL)
			{
				vars->exit_code = execute_line(vars);
				token_free_list(&vars->token_list);
			}
		}
	}
}

int	main(void)
{
	t_vars		vars;

	init_base_vars(&vars);
	allocate_env(&vars);
	signals_default();
	prompt_shell(&vars);
	return (0);
}
