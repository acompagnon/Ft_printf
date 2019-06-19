/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 21:44:58 by acompagn          #+#    #+#             */
/*   Updated: 2019/02/27 16:18:46 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*cpy;
	size_t	i;

	i = 0;
	if (!s || !(cpy = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
		cpy[i++] = s[start++];
	cpy[i] = '\0';
	return (cpy);
}
