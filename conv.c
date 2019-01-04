/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:20:59 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/04 18:06:31 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_pointer(va_list ap)
{
	unsigned long long	a;
	char				*keep;

	a = va_arg(ap, unsigned long long);
	keep = ft_itoa_addr(a);
	return (keep);
}

char		*ft_char(va_list ap, t_print *lst)
{
	int		tmp;
	char	*c;

	tmp = va_arg(ap, int);
	if (!(c = (char *)malloc(sizeof(char) * 2)))
		return (NULL);
	c[0] = (char)tmp;
	c[1] = 0;
	if (!tmp)
		lst->i++;
	return (c);
}

char		*ft_string(va_list ap)
{
	char	*s;
	char	*keep;

	s = va_arg(ap, char*);
	if (!s)
	{
		if (!(keep = (char *)malloc(sizeof(char) * 7)))
			return (NULL);
		keep[0] = '(';
		keep[1] = 'n';
		keep[2] = 'u';
		keep[3] = 'l';
		keep[4] = 'l';
		keep[5] = ')';
		keep[6] = '\0';
	}
	else
		keep = ft_strdup(s);
	return (keep);
}

char		*ft_unsigned(uintmax_t a)
{
	char		*base;
	char		*keep;

	base = "0123456789\0";
	keep = ft_itoa_base(a, base);
	return (keep);
}
