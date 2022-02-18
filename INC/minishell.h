/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 14:09:18 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/18 12:50:36 by xvoorvaa      ########   odam.nl         */
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
	T_REDIRECT_STDOUT_TO_FILE, /* > */
	T_REDIRECT_STDOUT_TO_FILE_APPEND, /* >> */
	T_REDIRECT_FILE_TO_STDIN, /* < */
	T_REDIRECT_FILE_TO_DELIMITER /* << */
};

typedef struct	s_token
{
	char			*content;
	int				separated_from_previous;
	enum e_token	token;
	struct s_token	*next;
}	t_token;

typedef struct s_vars
{
	char			**prompt;
	t_token			*token_list;
}	t_vars;

/*
	MINISHELL
*/

int		init_vars(t_vars *vars);

int		execute_line(t_vars vars);

/*
	FUNCTIONS
*/

int		exec_echo(t_vars vars);

/*
	LINKED LIST
*/

void	new_node(t_token **head, char *content, int token);

void	print_list(t_token *head);

void	print_token(t_token *head);

int		lstsize(t_token	*head);

t_token	*token_new(char *content, const enum e_token type);

t_token	*token_li_last(t_token *lst);

void	token_li_push_back(t_token **lst, t_token *new);

void	token_free_list(t_token **lst);

/*
	CHECK_CHAR
*/

int		check_delimiter(char *prompt);

int		check_redirect_stdin(char *prompt);

int		check_redirect_stdout_append(char *prompt);

int		check_redirect_stdout(char *prompt);

int		check_pipes(char *prompt);

/*
	OVERIG
*/

char	**ft_args_split(char *str);

void	m_splitargs_error(const char *s);

char	*m_copy_qword(char *dst, const char *str, size_t *i, size_t len);

char	*m_create_quotew(const char *s, size_t *index);

int		m_skip_quotew(const char *str, size_t *i, int *wordcount,
			int decrement_on_escape);

#endif
