/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_spaces.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/23 20:40:29 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/23 20:40:42 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

char *remove_spaces(char *str)
{
	int	i;
	int count;
	int	hadspace;

	i = 0;
	count = 0;
	hadspace = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			if (!hadspace)
			{
				str[count] = str[i];
				count++;
				hadspace = 1;
			}
		}
		else
		{
			hadspace = 0;
			str[count] = str[i];
			count++;
		}
		i++;
	}
	if (str[count] == ' ')
		count--;
	str[count] = '\0';
	return (str);
}
