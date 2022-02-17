// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   lexer.c                                            :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2022/02/17 12:23:00 by jobvan-d      #+#    #+#                 */
// /*   Updated: 2022/02/17 15:15:26 by xvoorvaa      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// #include <stdbool.h>

// /*
// OK:


// THEN: token expansion.
//  */

// // TODO \ escape.
// static void	loop_until_quote_closes(t_token *cur, const char *line, size_t *i)
// {
// 	char	quote_char;

// 	quote_char = line[*i];
// 	if (quote_char == '"')
// 		cur->token = T_LITERAL_EXPANDING;
// 	else if (quote_char == '\'') // TODO: Always true
// 		cur->token = T_LITERAL_NONEXPANDING;
// 	(*i)++;
// 	while (line[*i] != quote_char)
// 	{
// 		if (line[*i] == 0)
// 		{
// 			// TODO: error, quote not closed.
// 		}
// 		else if (line[*i] == '\\' && line[*i + 1] != 0)
// 		{
// 			(*i)++;
// 		}
// 		(*i)++;
// 	}
// 	(*i)++;
// }

// // TODO: # comments?
// // TODO: check if separated from the previous.
// static void	loop(t_token **tlst, t_token *cur, const char *line, size_t *i)
// {
// 	size_t	start_index;

// 	start_index = *i;
// 	while (line[*i])
// 	{
// 		if (line[*i] == '"' || line[*i] == '\'')
// 		{
// 			loop_until_quote_closes(cur, line, i);
// 			continue ;
// 		}
// 		(*i)++;
// 	}
// 	// TODO: now we're done with this word. Add the current token to the list,
// 	// TODO: list copy should take \ into account.
// 	// and repeat the process.
// }

// // TODO: copying should take escapes(\) into account!
// void	lex(t_token **tlst, const char *line)
// {
// 	t_token	*cur;
// 	size_t	i;

// 	i = 0;
// 	while (line[i] == ' ')
// 		i++;
// 	cur = token_new(NULL, T_UNKNOWN);
// 	if (!cur)
// 	{
// 		// TODO ERROR
// 	}
// 	cur->separated_from_previous = true;
// 	loop(tlst, cur, line, &i);	
// }
