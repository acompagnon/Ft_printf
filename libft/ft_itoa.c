/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:59:05 by acompagn          #+#    #+#             */
/*   Updated: 2019/02/27 15:49:21 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	char			*str;
	int				len;
	unsigned int	abs;
	unsigned int	tmp;

	len = (n < 0) ? 2 : 1;
	abs = (n < 0) ? -n : n;
	tmp = abs;
	while (tmp > 9)
	{
		len++;
		tmp /= 10;
	}
	if (!(str = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	str[len--] = '\0';
	while (abs > 9)
	{
		str[len--] = (abs % 10) + 48;
		abs /= 10;
	}
	str[len] = (abs % 10) + 48;
	if (n < 0)
		str[--len] = '-';
	return (str);
}
