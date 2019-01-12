/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:20:59 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/12 20:33:46 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_lst_init(t_print *lst)
{
	lst->i = 0;
	lst->a = 0;
	lst->keep = NULL;
}

void	ft_pointer(va_list ap, t_print *lst, t_flags *flags)
{
	unsigned long long	a;

	a = va_arg(ap, unsigned long long);
	ft_itoa_addr(a, lst, flags);
}

void	apply_width(t_print *lst, t_flags *flags, int len)
{
	int		i;

	i = 0;
	if (flags->hashtag == 2 || flags->hashtag == 3)
		len -= 2;
	while (i < len)
	{
		lst->buf[lst->i++] = flags->zero + 32;
		i++;
	}
}

void	ft_percent(t_print *lst, t_flags *flags, char format)
{
	if (flags->width > 1 && !flags->minus)
		string_width(lst, flags, flags->width - 1);
	if (lst->i + 1 >= BUFFER_SIZE)
		ft_empty_buf(lst);
	lst->buf[lst->i++] = format;
	if (flags->width > 1 && flags->minus)
		string_width(lst, flags, flags->width - 1);
}

void	ft_unsigned(uintmax_t a, t_print *lst, t_flags *flags)
{
	char		*base;

	base = "0123456789\0";
	ft_itoa_base(a, base, lst, flags);
}
