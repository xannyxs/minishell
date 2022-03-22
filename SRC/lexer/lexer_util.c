/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_util.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/28 18:30:25 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/22 14:51:42 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* ft_memcpy, ft_strndup_unsafe */
#include "ft_printf.h" /* ft_dprintf */

/* TODO: I don't like this. Perhaps lookup table? */
/* returns whether c is a token char. */
int	is_token_char_present(const char c)
{
	return (c == '\'' || c == '"' || c == '|' || c == '<' || c == '>');
}

static void	lex_word_copy(t_token *cur, const char *line, size_t start_index,
	size_t end_index)
{
	size_t	i;
	size_t	len;

	i = start_index;
	len = end_index - start_index;
	if (line[i] == '"' || line[i] == '\'')
	{
		i++;
		len -= 2;
	}
	cur->content = ft_strndup_unsafe(line + i, len);
	if (!cur->content)
	{
		malloc_fail();
	}
}

void	lex_finish_word(t_token **cur, const char *line,
	size_t *start_index, size_t end_index)
{
	t_token	*new_node;

	if (*start_index == end_index)
		return ;
	lex_word_copy(*cur, line, *start_index, end_index);
	*start_index = end_index;
	new_node = token_new(NULL, T_DEFAULT_TOKEN);
	if (!new_node)
	{
		malloc_fail();
	}
	(*cur)->next = new_node;
	*cur = (*cur)->next;
}

// No need to check if quote_char == '\'' because that is implied.
// Also, what a bummer that I cannot use my own ft_dprintf...
int	lex_set_quote_token_and_loop(t_token *cur, const char *line,
	size_t *i)
{
	char	quote_char;
	size_t	orig_i;

	orig_i = *i;
	quote_char = line[*i];
	if (quote_char == '"')
		cur->token = T_LITERAL_QUOTED;
	else
		cur->token = T_LITERAL_NONEXPANDING;
	(*i)++;
	while (line[*i] != quote_char)
	{
		if (line[*i] == 0)
		{
			ft_dprintf(2, "minishell: syntax error: quote %c at column %u \
did not close\n", quote_char, orig_i);
			return (-1);
		}
		(*i)++;
	}
	(*i)++;
	return (0);
}

// No need to check if char is pipe, because that is implied.
void	lex_check_other_token_and_loop(t_token *cur, const char *str,
	size_t *i)
{
	if (str[*i] == '<')
	{
		if (str[*i + 1] == '<')
		{
			cur->token = T_HEREDOC;
			(*i)++;
		}
		else
			cur->token = T_REDIRECT_FILE_TO_STDIN;
	}
	else if (str[*i] == '>')
	{
		if (str[*i + 1] == '>')
		{
			cur->token = T_REDIRECT_STDOUT_TO_FILE_APPEND;
			(*i)++;
		}
		else
			cur->token = T_REDIRECT_STDOUT_TO_FILE;
	}
	else
		cur->token = T_PIPE;
	(*i)++;
}
