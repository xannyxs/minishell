/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   splitargs_tmp_util.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 15:54:36 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/02/17 18:10:10 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdlib.h> /* exit */

void	m_splitargs_error(const char *s)
{
	ft_putstr_fd("Invalid argument: ", 2);
	ft_putendl_fd(s, 2);
	exit(1);
}

char	*m_copy_qword(char *dst, const char *str, size_t *i, size_t len)
{
	size_t	j;

	j = 0;
	while (j < len)
	{
		if (str[*i] == '\\')
		{
			(*i)++;
		}
		dst[j] = str[*i];
		(*i)++;
		j++;
	}
	dst[j] = 0;
	return (dst);
}

char	*m_create_quotew(const char *s, size_t *index)
{
	size_t	len;
	size_t	i;
	char	*ret;

	i = *index;
	m_skip_quotew(s, &i, NULL, 1);
	len = i - *index - 1;
	ret = malloc(len + 1);
	if (ret)
	{
		(*index)++;
		m_copy_qword(ret, s, index, len);
		(*index)++;
	}
	return (ret);
}

static void	m_skip_quotw_end(size_t *i, size_t orig_i, int *wordcount)
{
	if (*i - orig_i < 2)
		m_splitargs_error("quotes cannot be empty");
	if (wordcount != NULL)
		(*wordcount)++;
}

int	m_skip_quotew(const char *str, size_t *i, int *wordcount,
	int decrement_on_escape)
{
	int		orig_i;
	size_t	escapes;
	char	quotechar;

	orig_i = *i;
	quotechar = str[*i];
	(*i)++;
	escapes = 0;
	while (str[*i] != quotechar)
	{
		if (str[*i] == '\\')
		{
			(*i)++;
			escapes++;
		}
		if (str[*i] == 0)
			return (0);
		(*i)++;
	}
	m_skip_quotw_end(i, orig_i, wordcount);
	if (decrement_on_escape)
		*i -= escapes;
	return (1);
}
