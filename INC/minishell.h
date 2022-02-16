/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 14:09:18 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/16 16:25:17 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include "libft.h"

enum e_token {
	T_LITERAL,
	T_PIPE,
	T_REDIRECT,
	T_REDIRECT_FILE_TO_STDIN
};

typedef struct s_token
{
	char			*content;
	enum e_token	*token;
	struct s_token	*next;
}			t_token;

typedef struct s_parsing
{
	char	**prompt;
	int		flag_check;
	int		pipe_check;
	t_token	*tokenizer;
}	t_parsing;

/*
	MINISHELL
*/

int		init_parsing(t_parsing *parsing);


/*
	LINKED LIST
*/

void	new_node(t_token **head, char *content);

void	print_list(t_token *head);

#endif
