/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_str_arr.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 12:52:52 by jobvan-d      #+#    #+#                 */
/*   Updated: 2021/12/14 12:52:53 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

/* frees a null-terminated array of c strings. */
void	ft_free_str_arr(char **arr)
{
	char	**orig_arr;

	orig_arr = arr;
	while (*arr)
	{
		free(*arr);
		arr++;
	}
	free(orig_arr);
}
