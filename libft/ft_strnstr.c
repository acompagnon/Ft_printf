/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 18:16:23 by acompagn          #+#    #+#             */
/*   Updated: 2019/02/27 16:16:16 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t c;
	size_t size;

	i = 0;
	size = 0;
	while (needle[size])
		size++;
	if (!size)
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		c = 0;
		while (haystack[i + c] == needle[c] && i + c < len)
		{
			c++;
			if (c == size)
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (0);
}
