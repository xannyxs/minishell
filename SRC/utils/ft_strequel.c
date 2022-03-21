/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strequel.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/14 17:05:28 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/14 17:05:42 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_strequel(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '=' && str[len] != '\0')
		len++;
	return (len);
}
