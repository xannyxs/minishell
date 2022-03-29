/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_getenv.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 14:35:25 by xander        #+#    #+#                 */
/*   Updated: 2022/03/29 15:56:54 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* Several functions */

char	*ft_getenv(const char *name, char *environ[])
{
	int		i;
	size_t	namelen;
	char	*env;

	i = 0;
	namelen = ft_strlen(name);
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], name, namelen) == 0
			&& environ[i][namelen] == '=')
		{
			env = ft_substr(environ[i], namelen + 1, \
				ft_strlen(environ[i]) - namelen - 1);
			if (env == NULL)
				malloc_fail();
			return (env);
		}
		i++;
	}
	return (NULL);
}
