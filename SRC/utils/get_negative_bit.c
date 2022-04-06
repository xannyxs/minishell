/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_negative_bit.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jobvan-d <jobvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/06 13:26:58 by jobvan-d      #+#    #+#                 */
/*   Updated: 2022/04/06 13:34:38 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* returns an int with the negative bit set to 1, rest 0.
 * should be a macro, but norm won't allow it. */
int	get_negative_bit(void)
{
	return (1 << (sizeof(int) * 8 - 1));
}
