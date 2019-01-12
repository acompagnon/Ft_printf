/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 15:30:53 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/12 16:10:26 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_get_flags(char **format, t_flags *flags)
{
	if (**format == '-')
		flags->minus = 1;
	else if (**format == '+')
		flags->plus = 1;
	else if (**format == '#')
		flags->hashtag = 1;
	else if (**format == '0')
		flags->zero = 16;
	else if (**format == ' ')
		flags->space = 1;
	else if ((**format >= '0' && **format <= '9') || **format == '.')
		*format = get_nb(*format, flags);
	else if (**format == 'l')
		flags->l++;
	else if (**format == 'L')
		flags->llf++;
	else if (**format == 'h')
		flags->h++;
	else if (**format == 'j')
		flags->l += 2;
	else if (**format == 'z')
		flags->z++;
	else
		return (FORMAT_DOU ? flags->l = 2 : 1);
	return (0);
}

int		ft_get_type(char *format, va_list ap, t_print *lst, t_flags *flags)
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

void	print_lst_init(t_print *lst)
{
	lst->i = 0;
	lst->a = 0;
	lst->keep = NULL;
}

void	ft_printf_else(t_print *lst, char format)
{
	if (lst->i >= BUFFER_SIZE)
		ft_empty_buf(lst);
	lst->buf[lst->i++] = format;
}

int		ft_printf(const char *format, ...)
{
	t_print		lst;
	t_flags		flags;
	va_list		ap;

	print_lst_init(&lst);
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			ft_init_lst(&flags);
			while (*++format && !ft_get_flags((char **)&format, &flags))
				;
			if (ft_get_type((char *)format, ap, &lst, &flags))
				break ;
		}
		else
			ft_printf_else(&lst, *format);
		format++;
	}
	va_end(ap);
	write(1, lst.buf, lst.i);
	return (lst.a + lst.i);
}
