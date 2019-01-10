/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 15:30:53 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/10 13:13:31 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*get_nb(char *str, t_flags *flags)
{
	int		i;
	int		nb;
	int		p;
	int		w;

	i = 0;
	nb = 0;
	p = 0;
	w = 0;
	if (*str == '.')
	{
		p = 1;
		str++;
	}
	else 
		w = 1;
	while (*str && *str >= '0' && *str <= '9')
	{
		nb = nb * 10 + (*str - 48);
		str++;
		i++;
	}
	str--;
	if (p == 1)
	   	flags->precision = nb;
	else
		flags->width = nb;
	return (str);
}

void			ft_empty_buf(t_print *lst)
{
	write(1, lst->buf, lst->i);
	lst->a = lst->a + lst->i;
	lst->i = 0;
}

void			ft_put_in_buf(char *keep, t_print *lst, t_flags *flags)
{
	int		j;

	j = 0;
	flags->precision = -1;
	if (flags->width && !flags->minus)
		apply_width(lst, flags, ft_strlen(keep));
	while (keep[j])
	{
		if (lst->i >= BUFFER_SIZE)
			ft_empty_buf(lst);
		lst->buf[lst->i++] = keep[j++];
	}
	if (flags->width && flags->minus)
		apply_width(lst, flags, ft_strlen(keep));
	free(keep);
}

void		ft_init_lst(t_flags *flags)
{
	flags->minus = 0;
	flags->plus = 0;
	flags->hashtag = 0;
	flags->zero = 0;
	flags->space = 0;
	flags->width = 0;
	flags->precision = -1;
	flags->l = 0;
	flags->h = 0;
}

int			ft_get_flags(char **format, t_flags *flags)
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
	else if (**format >= '0' && **format <= '9')
		*format = get_nb(*format, flags);
	else if (**format == '.')
		*format = get_nb(*format, flags);
	else if (**format == 'l')
		flags->l++;
	else if (**format == 'h')
		flags->h++;
	else if (**format == 'j')
		flags->l += 2;
	else if (**format == 'z')
		flags->z++;
	else
		return ((**format == 'D' || **format == 'U' || **format == 'O') ? flags->l = 2 : 1);
	/*printf("minus = %d\n", flags->minus);
	printf("plus = %d\n", flags->plus);
	printf("hashtag = %d\n", flags->hashtag);
	printf("zero = %d\n", flags->zero);
	printf("space = %d\n", flags->space);
	printf("width = %d\n", flags->width);
	printf("precision = %d\n\n", flags->precision);*/
	return (0);
}

void		ft_get_type(const char *format, va_list ap, t_print *lst, t_flags *flags)
{
	char	*keep;

	keep = NULL;
	if (*format == 's')
		ft_string(ap, lst, flags);
	else if (*format == 'c')
		ft_char(ap, lst, flags);
	else if (*format == 'p')
		ft_pointer(ap, lst, flags);
	else if (*format == 'd' || *format == 'i')
		ft_decimal_itoa(ft_get_signed(ap, flags), lst, flags);
	else if (*format == 'x' || *format == 'X')
		ft_hexadecimal(ft_get_unsigned(ap, flags), *format, lst, flags);
	else if (*format == 'o')
		ft_octal(ft_get_unsigned(ap, flags), lst, flags);
	else if (*format == 'u')
		ft_unsigned(ft_get_unsigned(ap, flags), lst, flags);
	else if (*format == 'f')
	{
		if (!flags->l)
			keep = ftoa(va_arg(ap, double), flags->precision);
		else
			keep = lftoa(va_arg(ap, long double), flags->precision);
	}
	else if (*format == '%')
		lst->buf[lst->i++] = '%';
	if (keep)
		ft_put_in_buf(keep, lst, flags);
}

int				ft_printf(const char *format, ...)
{
	t_print		lst;
	t_flags		flags;
	va_list		ap;

	lst.i = 0;
	lst.a = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			ft_init_lst(&flags);
			while (*++format && !ft_get_flags((char **)&format, &flags))
				;
			ft_get_type(format, ap, &lst, &flags);
		}
		else
		{
			if (lst.i >= BUFFER_SIZE)
				ft_empty_buf(&lst);
			lst.buf[lst.i++] = *format;
		}
		format++;
	}
	va_end(ap);
	write(1, lst.buf, lst.i);
	return (lst.a + lst.i);
}
