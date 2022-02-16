/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 14:09:18 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/16 16:08:53 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include "libft.h"

enum e_token { T_LITERAL, T_PIPE, T_REDIRECT, T_REDIRECT_FILE_TO_STDIN };

typedef struct s_token
{
	char			**content;
	struct s_token	*next;
	enum e_token	*token;
}			t_token;

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
