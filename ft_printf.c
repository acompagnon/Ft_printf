/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 15:30:53 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/11 14:43:10 by acompagn         ###   ########.fr       */
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
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(keep);
	if (flags->minus)
		flags->zero = 0;
	if (flags->plus)
		flags->space = 0;
	if (keep[0] == '-' && !flags->plus)
		lst->buf[lst->i++] = '-';
	if (flags->plus && flags->zero)
		lst->buf[lst->i++] = (keep[0] == '-') ? '-' : '+';
	if (flags->width > len && !flags->minus)
		string_width(lst, flags, flags->width - len);
	if (keep[0] == '-')
		i++;
	while (keep[i])
	{
		if (lst->i >= BUFFER_SIZE)
			ft_empty_buf(lst);
		lst->buf[lst->i++] = keep[i++];
	}
	if (flags->width && flags->minus)
		string_width(lst, flags, flags->width - len);
	free(keep);
}

void		ft_init_lst(t_flags *flags)
{
	flags->minus = 0;
	flags->plus = 0;
	flags->hashtag = 0;
	flags->zero = 0;
	flags->space = 0;
	flags->width = -1;
	flags->precision = -1;
	flags->l = 0;
	flags->llf = 0;
	flags->h = 0;
	flags->z = 0;
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
	else if (**format == 'L')
		flags->llf++;
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
	printf("precision = %d\n", flags->precision);
	printf("flags->l = %d\n", flags->l);
	printf("flags->h = %d\n", flags->h);
	printf("flags->z = %d\n", flags->z);*/
	return (0);
}

char	*str_capitalize(char *keep)
{
	int		i;

	i = 0;
	while (keep[i])
		keep[i] = keep[i] + 32;
	return (keep);
}

int		ft_get_type(const char *format, va_list ap, t_print *lst, t_flags *flags)
{
	char	*keep;

	keep = NULL;
	if (*format == 's')
		ft_string(va_arg(ap, char *), lst, flags);
	else if (*format == 'c' || *format == 'C')
		ft_char(ap, lst, flags);
	else if (*format == 'p')
		ft_pointer(ap, lst, flags);
	else if (*format == 'd' || *format == 'D' || *format == 'i')
		ft_decimal_itoa(ft_get_signed(ap, flags), lst, flags);
	else if (*format == 'x' || *format == 'X')
		ft_hexadecimal(ft_get_unsigned(ap, flags), *format, lst, flags);
	else if (*format == 'o' || *format == 'O')
		ft_octal(ft_get_unsigned(ap, flags), lst, flags);
	else if (*format == 'u' || *format == 'U')
		ft_unsigned(ft_get_unsigned(ap, flags), lst, flags);
	else if (*format == 'f' || *format == 'F')
	{
		if (!flags->llf)
			keep = ftoa(va_arg(ap, double), flags->precision);
		else
			keep = lftoa(va_arg(ap, long double), flags->precision);
		if (*format == 'F' && (keep[0] == 'i' || keep[0] == 'n'))
			str_capitalize(keep);
		ft_put_in_buf(keep, lst, flags);
	}
	else if (*format)
		ft_percent(lst, flags, *format);
	else if (!*format)
		return (1);
	return (0);
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
			if (ft_get_type(format, ap, &lst, &flags))
				break;
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
