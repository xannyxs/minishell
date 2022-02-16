/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 14:09:18 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/16 15:54:22 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include "libft.h"

typedef struct s_parsing
{
	char	**prompt;
	int		flag_check;
	int		pipe_check;
	char	**commands;
	char	**text;
}	t_parsing;

/*
	MINISHELL
*/

int		start_parsing(char **prompt, t_parsing *parsing);

#endif
