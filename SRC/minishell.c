/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/14 18:11:55 by xander        #+#    #+#                 */
/*   Updated: 2022/02/23 16:51:47 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

static int	allocate_env(t_vars *vars)
{
	int			i;
	extern char	**environ;

	i = 0;
	while (environ[i] != NULL)
		i++;
	vars->environ = malloc((i + 1) * sizeof(char *));
	if (vars->environ == NULL)
		return (-1);
	i = 0;
	while (environ[i] != NULL)
	{
		vars->environ[i] = ft_strdup(environ[i]);
		if (vars->environ[i] == NULL)
		{
			ft_free_str_arr(vars->environ);
			return (-1);
		}
		i++;
	}
	vars->environ[i] = NULL;
	return (0);
}

int	main(void)
{
	int			err;
	char		*line;
	t_vars		vars;

	vars.token_list = NULL;
	vars.var_list = NULL;
	if (allocate_env(&vars) == -1)
		fatal_perror("malloc");
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
			print_token(vars.token_list);
			if (vars.token_list != NULL)
			{
				vars.exit_code = execute_line(&vars);
				token_free_list(&vars.token_list);
			}
		}
		// system("leaks minishell");
	}
	return (0);
}
