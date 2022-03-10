/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_util.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/10 21:19:18 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/03/10 21:21:05 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h> /* close */

/* closes a file descriptor if it's not -1 */
void	ft_close_fd(const int fd)
{
	if (fd != -1)
	{
		close(fd);
	}
}
