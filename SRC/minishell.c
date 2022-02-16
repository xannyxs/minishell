/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 18:11:55 by xander        #+#    #+#                 */
/*   Updated: 2022/02/16 14:04:20 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*str;

	str = (char *)342;
	while (1)
	{
		str = readline("minishell $> ");
		if (str == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		else
		{
			printf("[%s]\n", str);
			free(str);
		}
	}
	return (0);
}
