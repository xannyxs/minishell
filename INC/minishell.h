#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <stddef.h> /* size_t */

# define T_DEFAULT_TOKEN (T_LITERAL)

// TODO: maybe after the literals have been expanded,
// set to a more sane T_LITERAL so we don't have to if/else as much etc.
// TODO: >> <<
enum e_token {
	T_UNKNOWN,
	T_LITERAL,
	T_LITERAL_QUOTED,
	T_LITERAL_NONEXPANDING,
	T_PIPE,
	T_REDIRECT_STDOUT_TO_FILE, /* > */
	T_REDIRECT_STDOUT_TO_FILE_APPEND, /* >> */
	T_REDIRECT_FILE_TO_STDIN, /* < */
	T_HEREDOC /* << */
};

typedef struct s_envlist
{
	char				*variable;
	char				*content;
	struct s_envlist	*next;
}	t_envlist;

/* So, standard this is a singly linked list. But when the list is
 * "finalized", it becomes as doubly linked one so it's easier to parse it.
 * Note that ALL token functions do not support doubly linked lists! */
typedef struct s_token
{
	char			*content;
	int				separated_from_previous;
	enum e_token	token;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_vars
{
	unsigned char	exit_code;
	char			*old_pwd;
	char			*pwd;
	char			**environ;
	t_token			*token_list;
	t_envlist		*var_list;
}	t_vars;

/*
	MINISHELL
*/

int		init_vars(const char *line, t_vars *vars);

int		execute_line(t_vars *vars);

/*
	FUNCTIONS
*/

int		exec_echo(t_vars *vars);

int		exec_cd(t_vars *vars);

int		change_env_pwd(t_vars *vars);

int		exec_pwd(t_vars *vars);

int		exec_export(t_vars *vars);

int		exec_unset(t_vars *vars);

int		exec_env(t_vars *vars);

int		exec_exit(t_vars *vars);

int		exec_command(t_vars *vars);

/*
	LINKED LIST
*/

void	new_node(t_envlist **head, char *variable, char *content);

void	print_list(t_envlist *head);

void	print_token(t_token *head);

t_token	*token_new(char *content, const enum e_token type);

t_token	*token_li_last(t_token *lst);

void	token_li_push_back(t_token **lst, t_token *new);

t_token	*token_li_pop_back(t_token **tlst);

void	token_free(t_token *token);

void	token_free_list(t_token **lst);

void	token_remove_from_list(t_token **tlst, t_token *to_remove);

void	token_make_list_doubly_linked(t_token *lst);

/*
	LEXER
*/
int		lex(t_token **tlst, const char *line);

void	expand_token(t_token *el, const t_vars *vars);

void	lex_finish_word(t_token **cur, const char *line, size_t *start_index,
			size_t end_index);

int		lex_set_quote_token_and_loop(t_token *cur, const char *line,
			size_t *i);

void	lex_check_other_token_and_loop(t_token *cur, const char *str,
			size_t *i);

int		is_token_char_present(const char c);

int		lex_validate(t_token *lst);

/*
	ERRORS
*/

void	fatal_perror(const char *msg);

/*
	ACCESS
*/

char	**find_dir(char *envp[]);

char	*path_check(char *func, char **path);

#endif
