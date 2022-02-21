/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 18:11:55 by xander        #+#    #+#                 */
/*   Updated: 2022/02/21 17:07:00 by xvoorvaa      ########   odam.nl         */
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

	vars.prompt = NULL;
	vars.token_list = NULL;
	while (true)
	{
		line = readline("minishell $> ");
		vars.prompt = ft_args_split(line);
		if (vars.prompt == NULL)
		{
			printf("exit\n");
			exit(errno);
		}
		else
		{
			err = init_vars(&vars);
			if (err != 0)
				exit(errno);
			if (vars.token_list != NULL)
			{
				execute_line(&vars);
				free(line);
				free(vars.prompt);
				token_free_list(&vars.token_list);
			}
			// system("leaks minishell");
		}
	}
	return (0);
}
