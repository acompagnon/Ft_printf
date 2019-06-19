/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 21:55:01 by acompagn          #+#    #+#             */
/*   Updated: 2019/02/27 16:11:06 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*join;
	unsigned int	i;
	size_t			len;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(join = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (s1[++i])
		join[i] = s1[i];
	while (*s2)
		join[i++] = *s2++;
	join[i] = '\0';
	return (join);
}
