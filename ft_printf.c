/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 15:30:53 by acompagn          #+#    #+#             */
/*   Updated: 2019/06/19 16:48:35 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_get_flags(va_list ap, char **format, t_flags *flags)
{
	if (**format == '*')
		flags->width = get_wildcard(ap, flags, 1);
	else if (**format == '+' || **format == '-')
		**format == '-' ? flags->minus++ : flags->plus++;
	else if (**format == '#')
		flags->hashtag = 1;
	else if (**format == '0')
		flags->zero = 16;
	else if (**format == ' ')
		flags->space = 1;
	else if ((**format >= '0' && **format <= '9') || **format == '.')
		*format = get_nb(ap, *format, flags);
	else if (**format == 'l')
		flags->l++;
	else if (**format == 'L')
		flags->llf++;
	else if (**format == 'h')
		flags->h++;
	else if (**format == 'j')
		flags->j++;
	else if (**format == 'z')
		flags->z++;
	else
		return (FORMAT_DOU ? flags->l = 2 : 1);
	return (0);
}

static void	ft_printf_else(t_print *lst, char format)
{
	if (lst->i >= BUFFER_SIZE)
		ft_empty_buf(lst);
	lst->buf[lst->i++] = format;
}

int			ft_printf(const char *format, ...)
{
	t_print		lst;
	t_flags		flags;
	va_list		ap;

	print_lst_init(&lst);
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			ft_init_lst(&flags);
			while (*++format && !ft_get_flags(ap, (char **)&format, &flags))
				;
			if (ft_get_type((char *)format, ap, &lst, &flags))
				break ;
		}
		else
			ft_printf_else(&lst, *format);
		format++;
	}
	va_end(ap);
	write(1, lst.buf, lst.i);
	return (lst.a + lst.i);
}
