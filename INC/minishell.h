/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 14:09:18 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/17 14:45:51 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include "libft.h"

// TODO: maybe after the literals have been expanded,
// set to a more sane T_LITERAL so we don't have to if/else as much etc.
// TODO: >> <<
enum e_token {
	T_UNKNOWN,
	T_LITERAL,
	T_LITERAL_EXPANDING,
	T_LITERAL_NONEXPANDING,
	T_PIPE,
	T_REDIRECT_STDOUT_TO_FILE, // >
	T_REDIRECT_FILE_TO_STDIN // <
};

typedef struct s_token
{
	struct s_token	*next;
	char			*content;
	int				separated_from_previous;
	enum e_token	token;
}			t_token;

typedef struct s_parsing
{
	char	**prompt;
	int		flag_check;
	int		pipe_check;
	t_token	*tokenizer;
}	t_parsing;

t_token	*token_new(char *content, const enum e_token type);
t_token	*token_li_last(t_token *lst);
void	token_li_push_back(t_token **lst, t_token *new);
void	token_free(t_token *token);
void	token_li_free(t_token **lst);

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
