/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:17:06 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/11 22:45:39 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		lst_itoa_init(t_itoa *list)
{
	list->len = 1;
	list->keep_len = 0;
	list->size = 0;
	list->nb = 0;
}

static void		ft_itoa_base_2(t_itoa *list, t_print *lst, t_flags *flags)
{
	while (flags->precision > list->keep_len)
	{
		lst->buf[lst->i++] = '0';
		flags->precision--;
	}
	if (!list->zero_case || flags->hashtag == 4)
		while (list->keep[list->len])
		{
			if (lst->i >= BUFFER_SIZE)
				ft_empty_buf(lst);
			lst->buf[lst->i++] = list->keep[list->len++];
		}
	if (flags->width > list->size && flags->minus)
		apply_width(lst, flags, flags->width - list->size);
}

static void		ft_itoa_base_1(t_itoa *list, t_print *lst, t_flags *flags)
{
	(flags->hashtag == 4 && list->nb != 0) ? flags->width-- : 1;
	flags->plus ? flags->space = 0 : 1;
	if (flags->hashtag == 2 || flags->hashtag == 3)
		if (list->nb != 0 && flags->zero)
		{
			lst->buf[lst->i++] = '0';
			lst->buf[lst->i++] = (flags->hashtag == 2) ? 'x' : 'X';
		}
	if (flags->width > list->size && !flags->minus)
		apply_width(lst, flags, flags->width - list->size);
	if (flags->hashtag == 2 || flags->hashtag == 3)
		if (list->nb != 0 && !flags->zero)
		{
			lst->buf[lst->i++] = '0';
			lst->buf[lst->i++] = (flags->hashtag == 2) ? 'x' : 'X';
		}
	if (flags->hashtag == 4 && list->nb != 0)
	{
		lst->buf[lst->i++] = '0';
		list->keep_len++;
	}
	ft_itoa_base_2(list, lst, flags);
}

void		ft_itoa_base(uintmax_t a, char *base, t_print *lst, t_flags *flags)
{
	t_itoa				list;
	unsigned long long	tmp;
	unsigned long long	base_len;

	lst_itoa_init(&list);
	tmp = a;
	list.nb = a;
	base_len = ft_strlen(base);
	list.zero_case = (a == 0 && flags->precision == 0) ? 1 : 0;
	(flags->minus != 0 || flags->precision != -1) ? flags->zero = 0 : 1;
	while (a /= base_len)
		list.len++;
	list.keep[list.len] = '\0';
	list.size = (flags->precision != -1 && flags->precision > list.len) ?
		flags->precision : list.len;
	if (list.zero_case)
		list.size--;
	list.keep_len = list.len;
	while (list.len--)
	{
		list.keep[list.len] = base[tmp % base_len];
		tmp /= base_len;
	}
	list.len++;
	ft_itoa_base_1(&list, lst, flags);
}

static void		ft_itoa_2(t_itoa *list, t_print *lst, t_flags *flags)
{
	if (list->nbr < 0 || (list->nbr >= 0 && (flags->plus || flags->space)))
		flags->width--;
	(list->nbr < 0 && flags->zero != 0) ? lst->buf[lst->i++] = '-' : 1;
	if (list->nbr >= 0 && ((flags->plus && flags->zero) || flags->space))
		lst->buf[lst->i++] = flags->space ? ' ' : '+';
	if (flags->width > list->size && !flags->minus)
		apply_width(lst, flags, flags->width - list->size);
	if (list->nbr < 0 && flags->zero == 0)
		lst->buf[lst->i++] = '-';
	if (flags->zero == 0 && list->nbr >= 0 && flags->plus)
		lst->buf[lst->i++] = '+';
	while (flags->precision > list->keep_len)
	{
		lst->buf[lst->i++] = '0';
		flags->precision--;
	}
	if (!list->zero_case)
		while (list->keep[list->len])
		{
			if (lst->i >= BUFFER_SIZE)
				ft_empty_buf(lst);
			lst->buf[lst->i++] = list->keep[list->len++];
		}
	if (flags->width > list->size && flags->minus)
		apply_width(lst, flags, flags->width - list->size);
}

void		ft_itoa_dec(intmax_t nb, t_print *lst, t_flags *flags)
{
	t_itoa			list;
	uintmax_t		tmp;
	uintmax_t		abs;

	lst_itoa_init(&list);
	list.nbr = nb;
	abs = (nb < 0) ? -nb : nb;
	tmp = abs;
	list.zero_case = (nb == 0 && flags->precision == 0) ? 1 : 0;
	(flags->minus != 0 || flags->precision != -1) ? flags->zero = 0 : 1;
	while (abs /= 10)
		list.len++;
	list.keep[list.len] = '\0';
	list.size = (flags->precision != -1 && flags->precision > list.len) ?
		flags->precision : list.len;
	list.zero_case ? list.size-- : 1;
	list.keep_len = list.len;
	while (list.len--)
	{
		list.keep[list.len] = (tmp % 10) + 48;
		tmp /= 10;
	}
	list.len++;
	flags->plus ? flags->space = 0 : 1;
	ft_itoa_2(&list, lst, flags);
}

void		ft_octal(uintmax_t a, t_print *lst, t_flags *flags)
{
	char	*base;

	base = "01234567\0";
	if (flags->hashtag)
		flags->hashtag = 4;
	ft_itoa_base(a, base, lst, flags);
}

void		ft_hexadecimal(intmax_t a, char c, t_print *lst, t_flags *flags)
{
	char	*base;

	base = (c == 'x') ? "0123456789abcdef\0" : "0123456789ABCDEF\0";
	if (flags->hashtag && a != 0)
		flags->hashtag = (c == 'x') ? 2 : 3;
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
