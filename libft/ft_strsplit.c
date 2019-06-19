/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:25:45 by acompagn          #+#    #+#             */
/*   Updated: 2019/02/27 16:39:19 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char			**ft_strsplit(char const *s, char c)
{
	size_t	len;
	size_t	i;
	char	**string;
	int		a;

	i = 0;
	a = 0;
	if (!s)
		return (NULL);
	if (!(string = (char **)malloc(sizeof(char *) * (ft_count(s, c) + 1))))
		return (NULL);
	while (a < ft_count(s, c))
	{
		len = 0;
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			len++;
			i++;
		}
		string[a++] = ft_strsub(s, i - len, len);
	}
	string[a] = 0;
	return (string);
}
