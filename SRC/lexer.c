/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 12:23:00 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/02/24 13:03:49 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* ft_memcpy, ft_strndup_unsafe */

#include <stdlib.h> /* malloc */
#include <stdbool.h>

/*
OK:


THEN: token expansion.
 */

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
		fatal_error("malloc");
	}
}

static void	finish_word(t_token **cur, const char *line, size_t *start_index,
	size_t end_index)
{
	t_token	*new_node;

	if (*start_index == end_index)
		return ;
	lex_word_copy(*cur, line, *start_index, end_index);
	*start_index = end_index;
	new_node = token_new(NULL, T_DEFAULT_TOKEN);
	if (!new_node)
	{
		fatal_error("malloc");
	}
	(*cur)->next = new_node;
	*cur = (*cur)->next;
}

// No need to check if quote_char == '\'' because that is implied.
static void	loop_until_quote_closes(t_token *cur, const char *line, size_t *i)
{
	char	quote_char;

	quote_char = line[*i];
	if (quote_char == '"')
		cur->token = T_LITERAL_EXPANDING;
	else
		cur->token = T_LITERAL_NONEXPANDING;
	(*i)++;
	while (line[*i] != quote_char)
	{
		if (line[*i] == 0)
		{
			// TODO: error, quote not closed.
		}
		(*i)++;
	}
	(*i)++;
}

// TODO: >>
static int	lex_check_token(t_token *cur, const char *str)
{
	enum e_token	old_token;

	old_token = cur->token;
	if (*str == '|')
		cur->token = T_PIPE;
	else if (*str == '<')
	{
		cur->token = T_REDIRECT_FILE_TO_STDIN;
	}
	else if (*str == '>')
	{
		cur->token = T_REDIRECT_STDOUT_TO_FILE;
	}
	return (old_token != cur->token);
}

// TODO; clean up
static void	loop_words(t_token **cur, const char *line, size_t *i)
{
	size_t	start_index;

	(*cur)->separated_from_previous = true;
	start_index = *i;
	while (line[*i])
	{
		if (line[*i] == '"' || line[*i] == '\'')
		{
			if (*i > start_index)
			{
				finish_word(cur, line, &start_index, *i);
				(*cur)->separated_from_previous = false;
			}
			loop_until_quote_closes(*cur, line, i);
			finish_word(cur, line, &start_index, *i);
			(*cur)->separated_from_previous = false;
		}
		else if (lex_check_token(*cur, line + *i))
		{
			if (*i > start_index)
			{
				// TODO: this ugly. fix.
				(*cur)->token = T_LITERAL_EXPANDING;
				finish_word(cur, line, &start_index, *i);
				lex_check_token(*cur, line + *i);
				(*cur)->separated_from_previous = false;
			}
			(*i)++;
			finish_word(cur, line, &start_index, *i);
		}
		else if (line[*i] == ' ')
			break ;
		else
			(*i)++;
	}
	finish_word(cur, line, &start_index, *i);
}

// TODO: # comments?
// TODO: check if separated from the previous.
static void	loop(t_token *cur, const char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		loop_words(&cur, line, &i);
		while (line[i] == ' ')
			i++;
	}
	// TODO: now we're done with this word. Add the current token to the list,
	// and repeat the process
}

void	lex(t_token **tlst, const char *line)
{
	t_token	*cur;

	cur = token_new(NULL, T_DEFAULT_TOKEN);
	if (!cur)
	{
		fatal_error("malloc");
	}
	cur->separated_from_previous = true;
	token_li_push_back(tlst, cur);
	while (*line == ' ')
		line++;
	loop(cur, line);
	cur = token_li_pop_back(tlst);
	free(cur);
}
