/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 12:23:00 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/22 14:51:42 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h> /* free */
#include <stdbool.h>
#include <stdio.h>

/* I know it's kind of ugly to essentially do the same if statement twice
 * (see is_token_char_present in lexer_util.c), but it seems to me the 
 * cleanest way to write it. */
static int	process_token(t_token **cur, const char *line,
	size_t *start_index, size_t *i)
{
	if (line[*i] == '"' || line[*i] == '\'')
	{
		if (lex_set_quote_token_and_loop(*cur, line, i) == -1)
			return (-1);
	}
	else
	{
		lex_check_other_token_and_loop(*cur, line, i);
	}
	lex_finish_word(cur, line, start_index, *i);
	(*cur)->separated_from_previous = false;
	return (0);
}

static int	loop_words(t_token **cur, const char *line, size_t *i)
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
			if (process_token(cur, line, &start_index, i) == -1)
				return (-1);
		}
		else if (line[*i] == ' ')
			break ;
		else
			(*i)++;
	}
	lex_finish_word(cur, line, &start_index, *i);
	return (0);
}

static int	loop(t_token *cur, const char *line, size_t i)
{
	while (line[i])
	{
		if (loop_words(&cur, line, &i) == -1)
			return (-1);
		while (line[i] == ' ')
			i++;
	}
	return (0);
}

int	lex(t_token **tlst, const char *line)
{
	t_token	*cur;
	size_t	i;

	cur = token_new(NULL, T_DEFAULT_TOKEN);
	if (!cur)
		malloc_fail();
	cur->separated_from_previous = true;
	token_li_push_back(tlst, cur);
	i = 0;
	while (line[i] == ' ')
		i++;
	if (loop(cur, line, i) == -1)
		return (-1);
	cur = token_li_pop_back(tlst);
	free(cur);
	return (0);
}
