/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 21:01:12 by acompagn          #+#    #+#             */
/*   Updated: 2019/06/19 16:51:52 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		string_width(t_print *lst, t_flags *flags, int len)
{
	int		i;

	i = 0;
	if (flags->minus)
		flags->zero = 0;
	while (i < len)
	{
		(lst->i >= BUFFER_SIZE) ? ft_empty_buf(lst) : 1;
		lst->buf[lst->i++] = flags->zero + 32;
		i++;
	}
}

void		ft_char(va_list ap, t_print *lst, t_flags *flags)
{
	int		tmp;

	flags->precision = -1;
	tmp = va_arg(ap, int);
	if (flags->width && !flags->minus)
		string_width(lst, flags, flags->width - 1);
	if (lst->i >= BUFFER_SIZE)
		ft_empty_buf(lst);
	lst->buf[lst->i++] = (char)tmp;
	if (flags->width && flags->minus)
		string_width(lst, flags, flags->width - 1);
}

static char	*ft_null_string(char *keep)
{
	int		i;

	i = 0;
	keep[i++] = '(';
	keep[i++] = 'n';
	keep[i++] = 'u';
	keep[i++] = 'l';
	keep[i++] = 'l';
	keep[i++] = ')';
	keep[i] = '\0';
	return (keep);
}

void		ft_string(char *s, t_print *lst, t_flags *flags)
{
	int		len;
	char	keep[6];

	if (s)
	{
		len = ft_strlen(s);
		if (flags->precision != -1 && len > 0 && flags->precision < len)
			len = flags->precision;
		if (flags->width > len && !flags->minus)
			string_width(lst, flags, flags->width - len);
		while (*s)
		{
			if (lst->i >= BUFFER_SIZE)
				ft_empty_buf(lst);
			if (flags->precision >= 0)
				if (!flags->precision--)
					break ;
			lst->buf[lst->i++] = *s++;
		}
		if (flags->width > len && flags->minus)
			string_width(lst, flags, flags->width - len);
	}
	else
		ft_string(ft_null_string(keep), lst, flags);
}
