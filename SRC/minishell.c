/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 18:11:55 by xander        #+#    #+#                 */
/*   Updated: 2022/02/16 14:18:59 by xvoorvaa      ########   odam.nl         */
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
	int		err;
	char	*str;
	char	**prompt;

	prompt = NULL;
	while (true)
	{
		str = readline("minishell $> ");
		prompt = ft_split(str, ' ');
		if (prompt == NULL)
		{
			printf("exit\n");
			system("leaks minishell");
			exit(0);
		}
		else
		{
			err = start_parsing(prompt);
			if (err != 0)
				exit(0);
			free(str);
		}
	}
	return (0);
}
