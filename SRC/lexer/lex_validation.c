/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_validation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/02 18:13:21 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/31 14:12:31 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* ft_putendl_fd */

/* gets the token after token cur. 
 * returns T_UNKNOWN if there is no next token. */
static enum	e_token	token_after(const t_token *cur)
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
int	lex_validate(const t_token *lst)
{
	enum e_token	prev_token;

	prev_token = T_UNKNOWN;
	while (lst)
	{
		if (lst->token == T_PIPE)
		{
			if (prev_token != T_LITERAL || lst->next == NULL)
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
		prev_token = lst->token;
		lst = lst->next;
	}
	return (1);
}
