/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 18:11:55 by xander        #+#    #+#                 */
/*   Updated: 2022/02/22 18:57:47 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	int			err;
	char		*line;
	t_vars		vars;
	extern char	**environ;

	vars.token_list = NULL;
	vars.var_list = NULL;
	vars.environ = environ;
	while (true)
	{
		line = readline("minishell $> ");

		// TODO: eof
		if (line)
		{
			err = init_vars(line, &vars);
			free(line);
			if (err != 0)
				exit(errno);
			//print_token(vars.token_list);
			if (vars.token_list != NULL)
			{
				vars.err_output = execute_line(&vars);
				token_free_list(&vars.token_list);
			}
		}
		system("leaks minishell");
	}
	return (0);
}
