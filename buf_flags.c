/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 20:44:17 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/12 19:10:49 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*get_nb(va_list ap, char *str, t_flags *flags)
{
	int		nb;
	int		p;
	int		w;

	nb = 0;
	p = (*str == '.') ? 1 : 0;
	if (p)
		str++;
	if (*str == '*')
	{
		flags->precision = get_wildcard(ap, flags, 0);
		return (str);
	}
	w = p ? 0 : 1;
	while (*str && *str >= '0' && *str <= '9')
	{
		nb = nb * 10 + (*str - 48);
		str++;
	}
	str--;
	if (p)
		flags->precision = nb;
	else
		flags->width = nb;
	return (str);
}

void		ft_empty_buf(t_print *lst)
{
	write(1, lst->buf, lst->i);
	lst->a = lst->a + lst->i;
	lst->i = 0;
}

static void	ft_put_in_2(char *keep, t_print *lst, t_flags *flags, int len)
{
	int		i;

	i = (keep[0] == '-') ? 1 : 0;
	if (flags->zero == 0 && keep[0] != '-' && flags->plus)
		lst->buf[lst->i++] = '+';
	while (keep[i])
	{
		if (lst->i >= BUFFER_SIZE)
			ft_empty_buf(lst);
		lst->buf[lst->i++] = keep[i++];
	}
	if (flags->hashtag && flags->precision == 0)
		lst->buf[lst->i++] = '.';
	if (flags->width > len && flags->minus)
		string_width(lst, flags, flags->width - len);
	free(keep);
}

void		ft_put_in_buf(char *keep, t_print *lst, t_flags *flags)
{
	int		len;

	len = ft_strlen(keep);
	if ((keep[1] >= 'a' && keep[1] <= 'z') ||
		(keep[1] >= 'A' && keep[1] <= 'Z'))
	{
		flags->space = 0;
		flags->plus = 0;
		flags->hashtag = 0;
	}
	flags->zero = (flags->minus) ? 0 : flags->zero;
	flags->space = (flags->plus) ? 0 : flags->space;
	(flags->hashtag && flags->precision == 0) ? flags->width-- : 1;
	lst->i + 1 >= BUFFER_SIZE ? ft_empty_buf(lst) : 1;
	if (keep[0] != '-' && (flags->plus || flags->space))
		flags->width--;
	(keep[0] == '-' && flags->zero != 0) ? lst->buf[lst->i++] = '-' : 1;
	if (keep[0] != '-' && ((flags->plus && flags->zero) || flags->space))
		lst->buf[lst->i++] = flags->space ? ' ' : '+';
	if (flags->width > len && !flags->minus)
		string_width(lst, flags, flags->width - len);
	if (keep[0] == '-' && flags->zero == 0)
		lst->buf[lst->i++] = '-';
	ft_put_in_2(keep, lst, flags, len);
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
	flags->j = 0;
	flags->star = 0;
}
