/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoas_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 11:45:29 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/13 15:21:24 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		lst_itoa_init(t_itoa *list)
{
	list->len = 1;
	list->keep_len = 0;
	list->size = 0;
	list->nb = 0;
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

static void	ft_itoa_addr_2(t_itoa *list, t_print *lst, t_flags *flags)
{
	int		a;

	a = 0;
	list->size = (flags->precision != -1 && flags->precision > list->keep_len) ?
		flags->precision : list->keep_len;
	if (flags->width > list->size && !flags->minus)
		apply_width(lst, flags, flags->width - list->size);
	while (a < 2)
		lst->buf[lst->i++] = list->keep[a++];
	while (flags->precision > list->keep_len - 2)
	{
		if (lst->i >= BUFFER_SIZE)
			ft_empty_buf(lst);
		lst->buf[lst->i++] = '0';
		flags->precision--;
	}
	while (list->keep[a])
	{
		if (lst->i >= BUFFER_SIZE)
			ft_empty_buf(lst);
		lst->buf[lst->i++] = list->keep[a++];
	}
	if (flags->width && flags->minus)
		apply_width(lst, flags, flags->width - list->size);
}

void		ft_itoa_addr(uintmax_t a, t_print *lst, t_flags *flags)
{
	t_itoa			list;
	uintmax_t		tmp;
	char			*base;

	lst_itoa_init(&list);
	list.len = 3;
	tmp = a;
	base = "0123456789abcdef\0";
	while (a /= 16)
		list.len++;
	list.zero_case = (tmp == 0 && flags->precision == 0) ? 1 : 0;
	list.zero_case ? list.len-- : 1;
	list.zero_case ? list.size-- : 1;
	list.keep[list.len] = '\0';
	list.keep[0] = '0';
	list.keep[1] = 'x';
	list.keep_len = list.len;
	if (!list.zero_case)
		while (list.len-- > 2)
		{
			list.keep[list.len] = base[tmp % 16];
			tmp /= 16;
		}
	list.len++;
	ft_itoa_addr_2(&list, lst, flags);
}
