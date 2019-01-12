/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:17:06 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/12 18:52:04 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_itoa_base_2(t_itoa *list, t_print *lst, t_flags *flags)
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

static void	ft_itoa_base_1(t_itoa *list, t_print *lst, t_flags *flags)
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

static void	ft_itoa_2(t_itoa *list, t_print *lst, t_flags *flags)
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
