/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 18:02:59 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/05 18:29:14 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_putchar(char c)
{
	write(1, &c, 1);
}

void			print_long(unsigned char *c, t_float *lst)
{
	int 	k;
	int 	j;
	int		i;

	i = 0;
	j = 8;
	k = 4;
	lst->sign = (*(c + 9) & 128 ? 1 : 0);
	lst->intexp = (*(c + 9) & ~128) << 8 | *(c + 8);
	while (j--)
	{
		k = 8;
		while (k--)
			lst->mant[i++] = (*(c + j) & 1 << k) ? '1' : '0';
	}
	lst->mant[i] = '\0';
	lst->size = i;
}
