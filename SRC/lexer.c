/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 12:23:00 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/02/17 16:58:08 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* ft_memcpy */

#include <stdlib.h> /* malloc */
#include <stdbool.h>

/*
OK:


THEN: token expansion.
 */


// TODO: unused memory? quotes and escapes are not copied but are allocated.
static int	lex_word_copy(t_token *cur, const char *line, size_t start_index, size_t end_index)
{
	size_t	i;
	size_t	j;
	char	quote_char;
	
	i = start_index;
	j = 0;
	cur->content = malloc(end_index - start_index + 1);
	if (!cur->content)
	{
		// TODO: malloc fail
	}
	quote_char = 0;
	if (line[i] == '"' || line[i] == '\'')
	{
		quote_char = line[i];
		i++;
	}
	if (quote_char == '\'')
	{
		j = (end_index - i) - 1;
		ft_memcpy(cur->content, line + i, j);
	}
	else
	{
		while (i < end_index - 1)
		{
			if (line[i] == '\\')
				i++;
			cur->content[j] = line[i];
			i++;
			j++;
		}
		if (line[i] != quote_char)
		{
			cur->content[j] = line[i];
			i++;
			j++;
		}
	}
	cur->content[j] = 0;
}

static void	finish_word(t_token *cur, const char *line, size_t start_index,
	size_t *previous_final_index)
{

}

// TODO \ escape., \ newline.
static void	loop_until_quote_closes(t_token *cur, const char *line, size_t *i)
{
	char	quote_char;

	quote_char = line[*i];
	if (quote_char == '"')
		cur->token = T_LITERAL_EXPANDING;
	else if (quote_char == '\'') // TODO: Always true
		cur->token = T_LITERAL_NONEXPANDING;
	(*i)++;
	while (line[*i] != quote_char)
	{
		if (line[*i] == 0)
		{
			// TODO: error, quote not closed.
		}
		else if (line[*i] == '\\' && line[*i + 1] != 0)
		{
			(*i)++;
		}
		(*i)++;
	}
	(*i)++;
}

// TODO: # comments?
// TODO: check if separated from the previous.
static void	loop(t_token *cur, const char *line, size_t *i)
{
	size_t	start_index;
	size_t	previous_final_index;

	start_index = *i;
	previous_final_index = (size_t)-1;
	while (line[*i])
	{
		if (line[*i] == '"' || line[*i] == '\'')
		{
			//finish_word(cur, line, start_index, &previous_final_index);
			loop_until_quote_closes(cur, line, i);
			finish_word(cur, line, start_index, &previous_final_index);
			previous_final_index = i;
			continue ;
		}
		(*i)++;
	}
	// TODO: now we're done with this word. Add the current token to the list,
	// TODO: list copy should take \ into account.
	// and repeat the process.
}

// TODO: copying should take escapes(\) into account!
void	lex(t_token **tlst, const char *line)
{
	t_token	*cur;
	size_t	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	cur = token_new(NULL, T_UNKNOWN);
	if (!cur)
	{
		// TODO ERROR
	}
	cur->separated_from_previous = true;
	token_li_push_back(tlst, cur);
	loop(cur, line, &i);
}
