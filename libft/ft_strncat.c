/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 22:25:32 by acompagn          #+#    #+#             */
/*   Updated: 2019/02/27 16:14:28 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t len_s1;

	i = 0;
	len_s1 = ft_strlen(s1);
	while (s2[i] && i < n)
		s1[len_s1++] = s2[i++];
	s1[len_s1] = '\0';
	return (s1);
}
