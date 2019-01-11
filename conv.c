/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:20:59 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/11 19:44:13 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_pointer(va_list ap, t_print *lst, t_flags *flags)
{
	unsigned long long	a;

	a = va_arg(ap, unsigned long long);
	ft_itoa_addr(a, lst, flags);
}

void		ft_char(va_list ap, t_print *lst, t_flags *flags)
{
	int		tmp;

	flags->precision = -1;
	tmp = va_arg(ap, int);
	if (flags->width && !flags->minus)
		string_width(lst, flags, flags->width - 1);
	if (lst->i + 1 >= BUFFER_SIZE)
		ft_empty_buf(lst);
	lst->buf[lst->i++] = (char)tmp;
	if (flags->width && flags->minus)
		string_width(lst, flags, flags->width - 1);
}

void		apply_width(t_print *lst, t_flags *flags, int len)
{
	int		i;

	i = 0;
	//if (flags->minus != 0 || flags->precision != -1)
	//	flags->zero = 0;
	if (flags->hashtag == 2 || flags->hashtag == 3)
		len -= 2;
	/*if ((flags->hashtag == 2 || flags->hashtag == 3) && flags->zero)
	{
		lst->buf[lst->i++] = '0';
		lst->buf[lst->i++] = (flags->hashtag == 2) ? 'x' : 'X';
	}*/
	while (i < len)
	{
		lst->buf[lst->i++] = flags->zero + 32;
		i++;
	}
	/*if ((flags->hashtag == 2 || flags->hashtag == 3) && !flags->zero && !flags->minus)
	{
		lst->buf[lst->i++] = '0';
		lst->buf[lst->i++] = (flags->hashtag == 2) ? 'x' : 'X';
	}*/
}

void		string_width(t_print *lst, t_flags *flags, int len)
{
	int		i;

	i = 0;
	if (flags->minus)
		flags->zero = 0;
	while (i < len)
	{
		lst->buf[lst->i++] = flags->zero + 32;
		i++;
	}
}

void		ft_percent(t_print *lst, t_flags *flags, char format)
{
	if (flags->width > 1 && !flags->minus)
		string_width(lst, flags, flags->width - 1);
	lst->buf[lst->i++] = format;
	if (flags->width > 1 && flags->minus)
		string_width(lst, flags, flags->width - 1);
}

void		ft_string(char	*s, t_print *lst, t_flags *flags)
{
	int		len;
	char	keep[6];
	int		i;

	i = 0;
	if (s)
	{
		len = ft_strlen(s);
		if (flags->precision != -1 && len > 0 && flags->precision < len)
			len = flags->precision;
		if (flags->width > len && !flags->minus)
			string_width(lst, flags, flags->width - len);
		while (*s)
		{
			if (lst->i == BUFFER_SIZE)
				ft_empty_buf(lst);
			if (flags->precision >= 0)
				if (!flags->precision--)
					break;
			lst->buf[lst->i++] = *s++;
		}
		if (flags->width > len && flags->minus)
			string_width(lst, flags, flags->width - len);
	}
	else
	{
		keep[i++] = '(';
		keep[i++] = 'n';
		keep[i++] = 'u';
		keep[i++] = 'l';
		keep[i++] = 'l';
		keep[i++] = ')';
		keep[i] = '\0';
		ft_string(keep, lst, flags);
	}
}

void		ft_unsigned(uintmax_t a, t_print *lst, t_flags *flags)
{
	char		*base;

	base = "0123456789\0";
	ft_itoa_base(a, base, lst, flags);
}
