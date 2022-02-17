/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 18:11:55 by xander        #+#    #+#                 */
/*   Updated: 2022/02/17 16:04:07 by xvoorvaa      ########   odam.nl         */
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
	t_parsing	parsing;

	parsing.prompt = NULL;
	while (true)
	{
		line = readline("minishell $> ");
		parsing.prompt = ft_split(line, ' ');
		if (parsing.prompt == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		else
		{
			err = init_parsing(&parsing);
			if (err != 0)
				exit(0);
			free(line);
			free(parsing.prompt);
			token_free_list(&parsing.token_list);
			system("leaks minishell");
		}
	}
	return (0);
}
