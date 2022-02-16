/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:54:22 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:54:23 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

/* returns the amount of characters in s1 that are not in set. */
static void	m_strtrim_precount(char const *s1, char const *set,
	size_t *start, size_t *end)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s1);
	while (i < len && ft_str_contains_char((const char *)set, s1[i]))
	{
		i++;
	}
	*start = i;
	i = len;
	while (i > 0)
	{
		i--;
		if (!ft_str_contains_char((const char *)set, s1[i]))
			break ;
	}
	if (i < *start)
		i = *start;
	*end = i;
}

/* creates a new string from s1 with only characters that
 * do not appear in string set. */
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	size_t	start;
	size_t	end;
	size_t	i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	m_strtrim_precount(s1, set, &start, &end);
	ret = malloc((end - start + 1) + 1);
	if (ret == NULL)
		return (ret);
	i = start;
	while (i <= end)
	{
		ret[i - start] = s1[i];
		i++;
	}
	ret[i - start] = 0;
	return (ret);
}
