/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 18:02:59 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/12 13:12:57 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_long(unsigned char *c, t_float *lst)
{
	int	k;
	int	j;
	int	i;

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

int			check_double(double f, t_float *lst)
{
	int		nan;
	int		inf;
	int		i;

	nan = (f != f ? 1 : 0);
	inf = (lst->intexp == 2047 ? 1 : 0);
	i = 0;
	if (nan || inf)
	{
		if (!(lst->keep = (char *)malloc(sizeof(char) * (4 + lst->sign))))
			return (0);
		if (lst->sign && !nan)
			lst->keep[i++] = '-';
		lst->keep[i++] = nan ? 'n' : 'i';
		lst->keep[i++] = nan ? 'a' : 'n';
		lst->keep[i++] = nan ? 'n' : 'f';
		lst->keep[i] = '\0';
		return (0);
	}
	return (1);
}

int			check_long_double(long double f, t_float *lst)
{
	int		nan;
	int		inf;
	int		i;

	nan = (f != f ? 1 : 0);
	inf = (lst->intexp == 32767 ? 1 : 0);
	i = 0;
	if (nan || inf)
	{
		if (!(lst->keep = (char *)malloc(sizeof(char) * (4 + lst->sign))))
			return (0);
		if (lst->sign && !nan)
			lst->keep[i++] = '-';
		lst->keep[i++] = nan ? 'n' : 'i';
		lst->keep[i++] = nan ? 'a' : 'n';
		lst->keep[i++] = nan ? 'n' : 'f';
		lst->keep[i] = '\0';
		return (0);
	}
	return (1);
}
