/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_getenv.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 14:35:25 by xander        #+#    #+#                 */
/*   Updated: 2022/03/31 13:40:29 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* ft_str functioms */

/* attempts to get an environment variable. Returns the variable,
 * allocated using malloc. It must be freed. Returns NULL when
 * the variable was not found. */
char	*ft_getenv(const char *name, char *environ[])
{
	size_t	namelen;
	char	*env;

	namelen = ft_strlen(name);
	while (*environ != NULL)
	{
		if (ft_strncmp(*environ, name, namelen) == 0
			&& (*environ)[namelen] == '=')
		{
			env = ft_strdup(*environ + namelen + 1);
			if (env == NULL)
				malloc_fail();
			return (env);
		}
		environ++;
	}
	return (NULL);
}
