/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_getenv.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 14:35:25 by xander        #+#    #+#                 */
/*   Updated: 2022/03/08 15:06:37 by xander        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*ft_getenv(const char *name, char *environ[])
{
	int		i;
	char	*env;

	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], name, ft_strlen(name)) == 0)
		{
			env = ft_substr(environ[i], ft_strlen(name) + 1, \
				ft_strlen(environ[i]) - ft_strlen(name) - 1);
			if (env == NULL)
				fatal_perror("malloc");
			return (env);
		}
		i++;
	}
	return (NULL);
}
