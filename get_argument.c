/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argument.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:24:27 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/05 18:27:44 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char		*ft_get_lh(const char *format, int *h, int *l)
{
	*h = 0;
	*l = 0;
	while (*format == 'h' || *format == 'l' || *format == 'j')
	{
		if (*format == 'j')
			(*l) += 2;
		(*format == 'h') ? (*h)++ : (*l)++;
		format++;
	}
	return (format);
}

intmax_t		ft_get_signed(va_list ap, int h, int l)
{
	intmax_t	arg;

	if (l)
	{
		if (l > 1)
			arg = va_arg(ap, long long);
		else
			arg = va_arg(ap, long);
	}
	else if (h)
	{
		if (h > 1)
			arg = (char)va_arg(ap, int);
		else
			arg = (short)va_arg(ap, int);
	}
	else
		arg = va_arg(ap, int);
	return (arg);
}

uintmax_t		ft_get_unsigned(va_list ap, int h, int l)
{
	uintmax_t	arg;

	if (l)
	{
		if (l > 1)
			arg = va_arg(ap, unsigned long long);
		else
			arg = va_arg(ap, unsigned long);
	}
	else if (h)
	{
		if (h > 1)
			arg = (unsigned short)va_arg(ap, unsigned int);
		else
			arg = (unsigned char)va_arg(ap, unsigned int);
	}
	else
		arg = va_arg(ap, unsigned int);
	return (arg);
}
