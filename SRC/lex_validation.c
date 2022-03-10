/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_validation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/02 18:13:21 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/09 17:59:20 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* ft_putendl_fd */

/* gets the token before token cur.
 * returns T_UNKNOWN if there is no prior token. */
static enum	e_token	token_before(t_token *cur)
{
	enum e_token	token;

	token = T_UNKNOWN;
	if (cur->prev)
	{
		token = cur->prev->token;
	}
	return (token);
}

/* gets the token after token cur. 
 * returns T_UNKNOWN if there is no next token. */
static enum	e_token	token_after(t_token *cur)
{
	enum e_token	token;

	token = T_UNKNOWN;
	if (cur->next)
	{
		token = cur->next->token;
	}
	return (token);
}

/* does some basic validation of the input.
 * (ex. redirect is followed by a literal) */
// TODO: more accurate validation. for ex. > wc | cat is valid but shouldn't
int	lex_validate(t_token *lst)
{
	while (lst)
	{
		if (lst->token == T_PIPE)
		{
			if (token_before(lst) != T_LITERAL
				|| token_after(lst) != T_LITERAL)
			{
				ft_putendl_fd("minishell: syntax error, invalid pipe", 2);
				return (0);
			}
		}
		else if (token_is_redirect(lst))
		{
			if (token_after(lst) != T_LITERAL)
			{
				ft_putendl_fd("minishell: syntax error, \
invalid file redirection", 2);
				return (0);
			}
		}
		lst = lst->next;
	}
	return (1);
}
