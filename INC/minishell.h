/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 14:09:18 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/17 15:28:11 by xvoorvaa      ########   odam.nl         */
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
	char			*content;
	int				separated_from_previous;
	enum e_token	token;
	struct s_token	*next;
}			t_token;

typedef struct s_parsing
{
	char	**prompt;
	t_token	*token_list;
}	t_parsing;

/*
	MINISHELL
*/

int		init_parsing(t_parsing *parsing);

/*
	LINKED LIST
*/

void	new_node(t_token **head, char *content, int token);

void	print_list(t_token *head);

void	print_token(t_token *head);

t_token	*token_new(char *content, const enum e_token type);

t_token	*token_li_last(t_token *lst);

void	token_li_push_back(t_token **lst, t_token *new);

void	token_free(t_token *token);

void	token_li_free(t_token **lst);

int		free_list(t_token **head);

/*
	CHECK_CHAR
*/

int		check_redirect(char **prompt);

int		check_pipes(char **prompt);

#endif
