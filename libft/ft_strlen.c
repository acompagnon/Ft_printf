/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 14:21:51 by acompagn          #+#    #+#             */
/*   Updated: 2019/02/27 16:12:18 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (!s[i])
			return (i);
		if (!s[i + 1])
			return (i + 1);
		if (!s[i + 2])
			return (i + 2);
		if (!s[i + 3])
			return (i + 3);
		if (!s[i + 4])
			return (i + 4);
		if (!s[i + 5])
			return (i + 5);
		if (!(s[i + 6]))
			return (i + 6);
		if (!(s[i + 7]))
			return (i + 7);
		i += 7;
	}
	return (i);
}
