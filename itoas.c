/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:17:06 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/11 19:44:01 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_itoa_base(uintmax_t a, char *base, t_print *lst, t_flags *flags)
{
	int					len;
	int					size;
	int					zero_case;
	unsigned long long	tmp;
	unsigned long long	nb;
	unsigned long long	base_len;
	char				keep[21];

	int lennn = 0;
	len = 1;
	tmp = a;
	nb = a;
	base_len = ft_strlen(base);
	zero_case = (a == 0 && flags->precision == 0) ? 1 : 0;
	if (flags->minus != 0 || flags->precision != -1)
		flags->zero = 0;
	while (a /= base_len)
		len++;
	keep[len] = '\0';
	size = (flags->precision != -1 && flags->precision > len) ? flags->precision : len;
	if (zero_case)
		size--;
	lennn = len;
	while (len--)
	{
		keep[len] = base[tmp % base_len];
		tmp /= base_len;
	}
	len++;
	if (flags->hashtag == 4 && nb != 0)
		flags->width--;
	if (flags->plus)
		flags->space = 0;
	if ((flags->hashtag == 2 || flags->hashtag == 3) && nb != 0 && flags->zero)
	{
		lst->buf[lst->i++] = '0';
		lst->buf[lst->i++] = (flags->hashtag == 2) ? 'x' : 'X';
	}
	if (flags->width > size && !flags->minus)
		apply_width(lst, flags, flags->width - size);
	if ((flags->hashtag == 2 || flags->hashtag == 3) && nb != 0 && !flags->zero)
	{
		lst->buf[lst->i++] = '0';
		lst->buf[lst->i++] = (flags->hashtag == 2) ? 'x' : 'X';
	}
	if (flags->hashtag == 4 && nb != 0)
	{
		lst->buf[lst->i++] = '0';
		lennn++;
	}
	while (flags->precision > lennn)
	{
		lst->buf[lst->i++] = '0';
		flags->precision--;
	}
	if (!zero_case || flags->hashtag == 4)
		while (keep[len])
		{
			if (lst->i >= BUFFER_SIZE)
				ft_empty_buf(lst);
			lst->buf[lst->i++] = keep[len++];
		}
	if (flags->width > size && flags->minus)
		apply_width(lst, flags, flags->width - size);
}

void		ft_decimal_itoa(intmax_t nb, t_print *lst, t_flags *flags)
{
	int				len;
	int				size;
	int				zero_case;
	uintmax_t		tmp;
	uintmax_t		abs;
	char			keep[21];

	len = 1;
	abs = (nb < 0) ? -nb : nb;
	tmp = abs;
	zero_case = (nb == 0 && flags->precision == 0) ? 1 : 0;
	if (flags->minus != 0 || flags->precision != -1)
		flags->zero = 0;
	while (abs /= 10)
		len++;
	if (flags->precision - len > 0)
	{
		flags->precision -= len;
		len += flags->precision;
	}
	size = (nb < 0 || flags->plus || flags->space) + len;
	if (zero_case)
		size--;
	keep[len] = '\0';
	if (lst->i + len + 1 >= BUFFER_SIZE)
		ft_empty_buf(lst);
	while (len-- > 0)
	{
		keep[len] = (tmp % 10) + 48;
		tmp /= 10;
		if (len < flags->precision && flags->precision > size)
			keep[len] = '0';
	}
	len++;
	if (flags->plus)
		flags->space = 0;
	if (nb < 0 && flags->zero != 0)
		lst->buf[lst->i++] = '-';
	if ((flags->plus && nb >= 0 && flags->zero != 0) || (nb >= 0 && flags->space))
		lst->buf[lst->i++] = flags->space ? ' ' : '+';
	if (flags->width > size && !flags->minus)
		apply_width(lst, flags, flags->width - size);
	if (nb < 0 && flags->zero == 0)
		lst->buf[lst->i++] = '-';
	if (flags->zero == 0 && nb >= 0 && flags->plus)
		lst->buf[lst->i++] = '+';
	if (!zero_case)
		while (keep[len])
			lst->buf[lst->i++] = keep[len++];
	if (flags->width > size && flags->minus)
		apply_width(lst, flags, flags->width - size);
}

void		ft_octal(uintmax_t a, t_print *lst, t_flags *flags)
{
	char	*base;

	base = "01234567\0";
	if (flags->hashtag)
		flags->hashtag = 4;
	ft_itoa_base(a, base, lst, flags);
}

void		ft_hexadecimal(intmax_t a, char format, t_print *lst, t_flags *flags)
{
	char	*base;

	base = (format == 'x') ? "0123456789abcdef\0" : "0123456789ABCDEF\0";
	if (flags->hashtag && a != 0)
		flags->hashtag = (format == 'x') ? 2 : 3;
	ft_itoa_base(a, base, lst, flags);
}

void		ft_itoa_addr(uintmax_t a, t_print *lst, t_flags *flags)
{
	int				len;
	int				size;
	int				zero_case;
	uintmax_t		tmp;
	char			keep[20];
	char			*base;

	len = 3;
	tmp = a;
	base = "0123456789abcdef\0";
	while (a /= 16)
		len++;
	zero_case = (tmp == 0 && flags->precision == 0) ? 1 : 0;
	if (zero_case)
		len--;
	if (flags->precision - len > 0)
	{
		flags->precision -= len - 2;
		len += flags->precision;
	}
	keep[len] = '\0';
	keep[0] = '0';
	keep[1] = 'x';
	size = len;
	while (len-- > 2)
	{
		keep[len] = base[tmp % 16];
		tmp /= 16;
		if (len < flags->precision && flags->precision > size)
						keep[len] = '0';
	}
	if (flags->width != -1 && !flags->minus)
		apply_width(lst, flags, flags->width - size);
	if (lst->i + ft_strlen(keep) >= BUFFER_SIZE)
		ft_empty_buf(lst);
	while (keep[a])
		lst->buf[lst->i++] = keep[a++];
	if (flags->width && flags->minus)
		apply_width(lst, flags, flags->width - size);
}
