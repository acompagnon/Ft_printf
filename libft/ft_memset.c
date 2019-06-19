/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 18:30:58 by acompagn          #+#    #+#             */
/*   Updated: 2019/02/27 15:58:43 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *tmp;
	unsigned char t;

	tmp = (unsigned char*)b;
	t = (unsigned char)c;
	while (len > 0)
		tmp[--len] = t;
	return (b);
}
