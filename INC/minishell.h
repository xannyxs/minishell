#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <stddef.h> /* size_t */

# define T_DEFAULT_TOKEN (T_LITERAL)

/* create_argv_advanced statuses. note that these are all individual
 * bits, so they can be OR'ed. -1 is also OR'ed on fail. */
# define M_PS_REDIRECTED_STDOUT (1)
# define M_PS_REDIRECTED_STDIN (2)
# define M_PS_REDIRECTION_FAILED (4)
# define M_PS_EMPTY (8)

# define SUCCESS 0
# define ERROR 1

/* After literals are expanded, every literal is considered a T_LITERAL. */
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

typedef struct pipe_vars
{
	int		*infd;
	int		*outfd;
	char	infd_is_pipe;
	char	outfd_is_pipe;
}	t_pipe_vars;

/*
	MINISHELL
*/

int		init_vars(const char *line, t_vars *vars);

int		execute_line(t_vars *vars);

/*
	FUNCTIONS
*/

int		exec_echo(char *argv[], t_vars *vars);

int		exec_cd(char *argv[], t_vars *vars);

int		change_env_pwd(t_vars *vars);

int		change_env_oldpwd(t_vars *vars);

int		exec_pwd(char *argv[], t_vars *vars);

int		exec_export(char *argv[], t_vars *vars);

void	replace_dup_env(t_vars *vars, char *variable, char *content);

int		check_dup_env(t_vars vars, char *variable);

void	print_usr_env(t_envlist *temp);

void	print_sys_env(t_vars vars, int i);

int		exec_unset(char *argv[], t_vars *vars);

int		exec_env(char *argv[], t_vars *vars);

int		exec_exit(char *argv[], t_vars *vars);

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

void	token_make_list_doubly_linked(t_token *lst);

int		token_count_occurrences(t_token *lst, int (*f)(const t_token *));

t_token	*token_get_first_occurrence(t_token *lst, int (*f)(const t_token *));

int		token_is_literal(const t_token *tok);

int		token_is_redirect(const t_token *tok);

size_t	token_lst_size(t_token *lst);

/*
	LEXER
*/
int		lex(t_token **tlst, const char *line);

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

void	malloc_fail();

/*
	ACCESS
*/

char	**find_dir(char *envp[]);

char	*path_check(char *func, char **path);

char	*ft_getenv(const char *name, char *environ[]);

/*
	PIPE EXECUTING
*/

char	*pathresolve_tryfind(char *name, char **envp);

int		execute_multiple(t_vars *vars);

void	do_redirect(t_token **tlst, int *infd, int *outfd, int *status);

void	redir_heredoc(t_token *tok, int *infd, int *status);

void	ft_close_fd(const int fd);

/*
	create_argv
*/
char	**create_argv_advanced(t_token **lst, int *infd, int *outfd,
			int *status);

/*
	var expansion
*/
void	expand_token(t_token *el, const t_vars *vars);

char	*ve_get_part(size_t i, char **cstr, const t_vars *vars);

char	*ve_strfjoin(char *a, char *b);

/*
	UTILS
*/

void	allocate_env(t_vars *vars);

int		ft_strequel(const char *str);

int		ft_getargc(char *argv[]);

char	*remove_spaces(char *str);

int		ft_valued_chars(char *argv);

/*
	main thread redirection and restoring
 */

void	rr_restore_redirs(int *fds, int *old_fds, int status);

void	rr_check_redirections(t_vars *vars, int *old_fds);

/*
	SIGNALS
*/

void	sighandler_default(int sig);

void	sighandler_pipes(int sig);

void	sighandler_pipes_quit(int sig);

void	signals(void);

void	signals_child(void);

void	deactivate_signals(void);

#endif
