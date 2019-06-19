/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 10:24:44 by acompagn          #+#    #+#             */
/*   Updated: 2019/02/27 16:40:28 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	t;

	t = ft_strlen(s);
	while (s[t] != (unsigned char)c)
		if (!t--)
			return (NULL);
	return (&((char *)s)[t]);
}
