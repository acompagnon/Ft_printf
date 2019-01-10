/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:17:06 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/10 13:38:03 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_itoa_base(uintmax_t a, char *base, t_print *lst, t_flags *flags)
{
	unsigned long long	len;
	unsigned long long	tmp;
	unsigned long long	base_len;
	unsigned long long	size;
	char				keep[21];

	len = 1;
	tmp = a;
	base_len = ft_strlen(base);
	if (flags->precision != -1 && !flags->minus)
		flags->zero = 16;
	while (a /= base_len)
		len++;
	keep[len] = '\0';
	size = len;
	while (len--)
	{
		keep[len] = base[tmp % base_len];
		tmp /= base_len;
	}
	if (flags->precision != -1)
		apply_width(lst, flags, size);
	if (flags->width && !flags->minus)
		apply_width(lst, flags, size);
	if (lst->i + ft_strlen(keep) >= BUFFER_SIZE)
		ft_empty_buf(lst);
	while (keep[a])
		lst->buf[lst->i++] = keep[a++];
	if (flags->width && flags->minus)
		apply_width(lst, flags, size);
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
	while (abs /= 10)
		len++;
	if (flags->precision - len > 0)
	{
		flags->precision -= len;
		len += flags->precision;
	}
	size = ((nb < 0 && !flags->plus) || flags->plus || flags->space) ? len + 1 : len;
	if (zero_case)
		size--;
	keep[len] = '\0';
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
	{
		apply_width(lst, flags, flags->width - size);
	}
}

void		ft_octal(uintmax_t a, t_print *lst, t_flags *flags)
{
	char	*base;

	base = "01234567\0";
	if (flags->minus)
		flags->zero = 0;
	ft_itoa_base(a, base, lst, flags);
}

void		ft_hexadecimal(intmax_t a, char format, t_print *lst, t_flags *flags)
{
	char	*base;

	base = (format == 'x') ? "0123456789abcdef\0" : "0123456789ABCDEF\0";
	ft_itoa_base(a, base, lst, flags);
}

void		ft_itoa_addr(uintmax_t a, t_print *lst, t_flags *flags)
{
	int				len;
	int				size;
	uintmax_t		tmp;
	char			keep[20];
	char			*base;

	len = 3;
	tmp = a;
	base = "0123456789abcdef\0";
	while (a /= 16)
		len++;
	keep[len] = '\0';
	keep[0] = '0';
	keep[1] = 'x';
	size = len;
	while (len-- > 2)
	{
		keep[len] = base[tmp % 16];
		tmp /= 16;
	}
	if (flags->width && !flags->minus)
		apply_width(lst, flags, size);
	if (lst->i + ft_strlen(keep) >= BUFFER_SIZE)
		ft_empty_buf(lst);
	while (keep[a])
		lst->buf[lst->i++] = keep[a++];
	if (flags->width && flags->minus)
		apply_width(lst, flags, size);
}
