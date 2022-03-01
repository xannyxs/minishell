/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 12:23:00 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/01 13:54:10 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h> /* free */
#include <stdbool.h>

/* I know it's kind of ugly to essentially do the same if statement twice
 * (see is_token_char_present in lexer_util.c), but it seems to me the 
 * cleanest way to write it. */
static void	process_token(t_token **cur, const char *line,
	size_t *start_index, size_t *i)
{
	if (line[*i] == '"' || line[*i] == '\'')
	{
		lex_set_quote_token_and_loop(*cur, line, i);
	}
	else
	{
		lex_check_other_token_and_loop(*cur, line, i);
	}
	lex_finish_word(cur, line, start_index, *i);
	(*cur)->separated_from_previous = false;
}

static void	loop_words(t_token **cur, const char *line, size_t *i)
{
	size_t	start_index;

	(*cur)->separated_from_previous = true;
	start_index = *i;
	while (line[*i])
	{
		if (is_token_char_present(line[*i]))
		{
			if (*i > start_index)
			{
				lex_finish_word(cur, line, &start_index, *i);
				(*cur)->separated_from_previous = false;
			}
			process_token(cur, line, &start_index, i);
		}
		else if (line[*i] == ' ')
			break ;
		else
			(*i)++;
	}
	lex_finish_word(cur, line, &start_index, *i);
}

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
}

void	lex(t_token **tlst, const char *line)
{
	t_token	*cur;

	cur = token_new(NULL, T_DEFAULT_TOKEN);
	if (!cur)
	{
		fatal_perror("malloc");
	}
	cur->separated_from_previous = true;
	token_li_push_back(tlst, cur);
	while (*line == ' ')
		line++;
	loop(cur, line);
	cur = token_li_pop_back(tlst);
	free(cur);
}
