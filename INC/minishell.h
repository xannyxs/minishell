/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 14:09:18 by xvoorvaa      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2022/02/17 14:59:23 by xvoorvaa      ########   odam.nl         */
=======
/*   Updated: 2022/02/17 14:53:07 by xvoorvaa      ########   odam.nl         */
>>>>>>> 24bd83e833d4ec05cad178ac9e2eec3b6d011b3d
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include "libft.h"

enum e_token {
	T_UNKNOWN,
	T_LITERAL,
	T_PIPE,
	T_REDIRECT,
	T_REDIRECT_FILE_TO_STDIN
};

typedef struct s_token
{
	char			*content;
	enum e_token	token;
	struct s_token	*next;
}			t_token;

typedef struct s_parsing
{
	char	**prompt;
	int		flag_check;
	int		pipe_check;
	t_token	*tokenizer;
}	t_parsing;

<<<<<<< HEAD
t_token	*token_new(char *content, const enum e_token type);
t_token	*token_li_last(t_token *lst);
void	token_li_push_back(t_token **lst, t_token *new);
void	token_free(t_token *token);
void	token_li_free(t_token **lst);
=======
>>>>>>> 24bd83e833d4ec05cad178ac9e2eec3b6d011b3d

/*
	MINISHELL
*/

int		init_parsing(t_parsing *parsing);

/*
	LINKED LIST
*/

void	new_node(t_token **head, char *content);

void	print_list(t_token *head);

t_token	*token_new(char *content, const enum e_token type);

t_token	*token_li_last(t_token *lst);

<<<<<<< HEAD

=======
>>>>>>> 24bd83e833d4ec05cad178ac9e2eec3b6d011b3d
void	token_li_push_back(t_token **lst, t_token *new);

#endif
