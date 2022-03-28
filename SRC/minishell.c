/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 18:11:55 by xander        #+#    #+#                 */
/*   Updated: 2022/03/28 15:17:28 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	init_base_vars(t_vars *vars)
{
	vars->token_list = NULL;
	vars->var_list = NULL;
	vars->old_pwd = NULL;
	vars->pwd = NULL;
	vars->exit_code = 0;
}

// TODO: norm
int	main(void)
{
	int			err;
	char		*line;
	t_vars		vars;

	init_base_vars(&vars);
	allocate_env(&vars);
	signals_default();
	while (true)
	{
		line = readline("\e[1;36mminishell \e[0;32m$> \e[0m");
		add_history(line);
		if (!line)
			exit(vars.exit_code);
		else if (*line != 0)
		{
			err = init_vars(line, &vars);
			free(line);
			if (err != 0)
			{
				token_free_list(&vars.token_list);
				continue ;
			}
			// print_token(vars.token_list);
			if (vars.token_list != NULL)
			{
				vars.exit_code = execute_line(&vars);
				token_free_list(&vars.token_list);
			}
		}
	}
	return (0);
}
