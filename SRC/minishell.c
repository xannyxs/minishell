/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 18:11:55 by xander        #+#    #+#                 */
/*   Updated: 2022/02/16 12:56:14 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	char	*str;

	str = (char *)342;
	while (str)
	{
		str = readline("hallo?");
		printf("%s", str);
	}
	return (0);
}
