/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argument.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:24:27 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/12 19:01:20 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			get_wildcard(va_list ap, t_flags *flags, int ok)
{
	int		tmp;

	flags->star = 1;
	tmp = va_arg(ap, int);
	if (!ok && tmp < 0)
		return (flags->precision);
	if (ok && tmp < 0)
		flags->minus = -1;
	if (tmp < 0)
		tmp = -tmp;
	if (!ok)
		flags->minus = 1;
	return (tmp);
}

intmax_t	ft_get_signed(va_list ap, t_flags *flags)
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

uintmax_t	ft_get_unsigned(va_list ap, t_flags *flags)
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

int			ft_get_type(char *format, va_list ap, t_print *lst, t_flags *flags)
{
	if (*format == 's')
		ft_string(va_arg(ap, char *), lst, flags);
	else if (*format == 'c' || *format == 'C')
		ft_char(ap, lst, flags);
	else if (*format == 'p')
		ft_pointer(ap, lst, flags);
	else if (*format == 'd' || *format == 'D' || *format == 'i')
		ft_itoa_dec(ft_get_signed(ap, flags), lst, flags);
	else if (*format == 'x' || *format == 'X')
		ft_hexadecimal(ft_get_unsigned(ap, flags), *format, lst, flags);
	else if (*format == 'o' || *format == 'O')
		ft_octal(ft_get_unsigned(ap, flags), lst, flags);
	else if (*format == 'u' || *format == 'U')
		ft_unsigned(ft_get_unsigned(ap, flags), lst, flags);
	else if (*format == 'f' || *format == 'F')
		float_call(ap, lst, flags, *format);
	else if (*format)
		ft_percent(lst, flags, *format);
	else if (!*format)
		return (1);
	return (0);
}
