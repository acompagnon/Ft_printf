/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argument.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:24:27 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/11 12:05:59 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*void		print(intmax_t nb)
{
	int		k;

	k = 64;
	while (k--)
		write(1, ((1ULL << k) & nb ? "1" : "0"), 1);
	write(1, "\n", 1);;
}*/

intmax_t		ft_get_signed(va_list ap, t_flags *flags)
{
	intmax_t	arg;

	if (flags->z)
		arg = va_arg(ap, ssize_t);
	else if (flags->l)
	{
		if (flags->l > 1)
			arg = va_arg(ap, long long);
		else
			arg = va_arg(ap, long);
	}
	else if (flags->h)
	{
		if (flags->h > 1)
			arg = (char)va_arg(ap, int);
		else
			arg = (short)va_arg(ap, int);
	}
	else
		arg = va_arg(ap, int);
	return (arg);
}

uintmax_t		ft_get_unsigned(va_list ap, t_flags *flags)
{
	uintmax_t	arg;

	if (flags->z)
		arg = va_arg(ap, size_t);
	else if (flags->l)
	{
		if (flags->l > 1)
			arg = va_arg(ap, unsigned long long);
		else
			arg = va_arg(ap, unsigned long);
	}
	else if (flags->h)
	{
		if (flags->h > 1)
			arg = (unsigned char)va_arg(ap, unsigned int);
		else
			arg = (unsigned short)va_arg(ap, unsigned int);
	}
	else
		arg = va_arg(ap, unsigned int);
	return (arg);
}
