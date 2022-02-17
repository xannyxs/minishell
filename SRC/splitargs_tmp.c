/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   splitargs_tmp.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 15:54:40 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/02/17 18:10:06 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

#include <stdlib.h> /* malloc */

static int	m_count_words(const char *str)
{
	size_t	i;
	int		wordcount;
	char	mode;

	wordcount = 0;
	i = 0;
	mode = 0;
	while (str[i] != 0)
	{
		while (str[i] != ' ')
		{
			if (str[i] == '\'' || str[i] == '"')
				if (!m_skip_quotew(str, &i, &wordcount, 0))
					m_splitargs_error("quote was not closed");
			if (str[i] == 0)
				return (wordcount + 1);
			i++;
		}
		wordcount++;
		while (str[i] == ' ')
			i++;
	}
	return (wordcount);
}

/* creates and allocs a "word", and updates the index for s. */
static char	*m_create_word(const char *s, size_t *index)
{
	char	*ret;
	size_t	j;
	size_t	i;
	size_t	len;

	i = *index;
	j = i;
	if (s[i] == '\'' || s[i] == '"')
	{
		return (m_create_quotew(s, index));
	}
	while (s[i] != ' ' && s[i] != 0)
	{
		i++;
	}
	len = i - j;
	ret = malloc(len + 1);
	if (ret != NULL)
	{
		ft_memcpy(ret, s + j, len);
		ret[len] = 0;
		*index = j + len;
	}
	return (ret);
}

static int	m_copy_to_array(char const *s, char **r, size_t n_words)
{
	size_t	i;
	size_t	current_word;

	i = 0;
	current_word = 0;
	while (s[i] != 0 && current_word < n_words)
	{
		r[current_word] = m_create_word(s, &i);
		if (r[current_word] == NULL)
			return (0);
		current_word++;
		while (s[i] == ' ' && s[i] != 0)
			i++;
	}
	r[current_word] = 0;
	return (1);
}

char	**ft_args_split(char *str)
{
	char	**ret;
	size_t	n_words;

	if (str == NULL)
		return ((char **)str);
	while (*str == ' ')
		str++;
	n_words = m_count_words(str);
	ret = malloc((n_words + 1) * sizeof(char *));
	if (ret == NULL)
		return (ret);
	if (!m_copy_to_array(str, ret, n_words))
	{
		ft_free_str_arr(ret);
		ret = NULL;
	}
	return (ret);
}
