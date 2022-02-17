/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 18:11:55 by xander        #+#    #+#                 */
/*   Updated: 2022/02/17 17:36:01 by xvoorvaa      ########   odam.nl         */
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
			exit(errno);
		}
		else
		{
			err = init_parsing(&parsing);
			if (err != 0)
				exit(0);
			free(line);
		}
	}
	return (0);
}
