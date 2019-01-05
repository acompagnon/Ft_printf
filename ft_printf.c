/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 15:30:53 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/05 19:49:31 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_nb(const char *str)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	if (*str == '.')
		str++;
	if (*str == '+' || *str == '-')
		str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		nb = nb * 10 + (*str - 48);
		str++;
		i++;
	}
	return (nb);
}

void			ft_empty_buf(t_print *lst)
{
	write(1, lst->buf, lst->i);
	ft_bzero(lst->buf, (BUFFER_SIZE + 1));
	lst->i = 0;
}

void			ft_put_in_buf(char *keep, t_print *lst)
{
	int		j;

	j = 0;
	while (keep[j])
	{
		if (lst->i >= BUFFER_SIZE)
		{
			lst->a = lst->a + lst->i;
			ft_empty_buf(lst);
		}
		lst->buf[lst->i++] = keep[j++];
	}
	free(keep);
}

const char		*ft_get_flags(const char *format, t_flags *flags)
{
	flags->minus = (*format == '-') ? 1 : 0;
	format = flags->minus ? format++ : format;
	flags->plus = (*format == '+') ? 1 : 0;
	format = flags->plus ? format++ : format;
	flags->hashtag = (*format == '#') ? 1 : 0;
	format = flags->hashtag ? format++ : format;
	flags->zero = (*format == '0') ? 1 : 0;
	format = flags->zero ? format++ : format;
	flags->space = (*format == ' ') ? 1 : 0;
	format = flags->space ? format++ : format;
	flags->width = (*format >= '0' && *format <= '9') ? get_nb(format) : 0;
	if (flags->width)
		while (*format >= '0' && *format <= '9')
			format++;
	flags->precision = (*format == '.') ? get_nb(format) : 6;
	while (*format == '.')
		format++;
	while (*format >= '0' && *format <= '9')
		format++;
	/*printf("minus = %d\n", flags->minus);
	printf("plus = %d\n", flags->plus);
	printf("hashtag = %d\n", flags->hashtag);
	printf("zero = %d\n", flags->zero);
	printf("space = %d\n", flags->space);
	printf("width = %d\n", flags->width);
	printf("precision = %d\n", flags->precision);*/
	return (format);
}

const char		*ft_get_type(const char *format, va_list ap, t_print *lst, t_flags *flags)
{
	int		h;
	int		l;
	char	*keep;

	keep = NULL;
	format = ft_get_flags(format, flags);
	format = ft_get_lh(format, &h, &l);
	if (*format == 's')
		keep = ft_string(ap);
	if (*format == 'c')
		keep = ft_char(ap, lst);
	if (*format == 'p')
		keep = ft_pointer(ap);
	if (*format == 'd' || *format == 'i')
		keep = ft_decimal_itoa(ft_get_signed(ap, h, l));
	if (*format == 'D')
		keep = ft_decimal_itoa(ft_get_signed(ap, h, 1));
	if (*format == 'x' || *format == 'X')
		keep = ft_hexadecimal(ft_get_unsigned(ap, h, l), format);
	if (*format == 'o')
		keep = ft_octal(ft_get_unsigned(ap, h, l), keep);
	if (*format == 'U')
		keep = ft_unsigned(ft_get_unsigned(ap, h, 1));
	if (*format == 'u')
		keep = ft_unsigned(ft_get_unsigned(ap, h, l));
	if (*format == 'f')
		keep = ftoa(va_arg(ap, double), flags->precision);
	if (keep)
		ft_put_in_buf(keep, lst);
	return (format);
}

int				ft_printf(const char *format, ...)
{
	t_print		lst;
	t_flags		flags;
	va_list		ap;

	lst.i = 0;
	lst.a = 0;
	va_start(ap, format);
	ft_bzero(lst.buf, (BUFFER_SIZE + 1));
	while (*format)
	{
		if (*format == '%' && *++format != '%')
			format = ft_get_type(format, ap, &lst, &flags);
		else
		{
			if (lst.i >= BUFFER_SIZE)
			{
				lst.a = lst.a + lst.i;
				ft_empty_buf(&lst);
			}
			lst.buf[lst.i++] = *format;
		}
		format++;
	}
	va_end(ap);
	write(1, lst.buf, lst.i);
	return (lst.a + lst.i);
}
