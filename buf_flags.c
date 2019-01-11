/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 20:44:17 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/11 20:44:33 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_nb(char *str, t_flags *flags)
{
	int		nb;
	int		p;
	int		w;

	nb = 0;
	p = 0;
	if (*str == '.')
	{
		p = 1;
		str++;
	}
	w = (p == 1) ? 0 : 1;
	while (*str && *str >= '0' && *str <= '9')
	{
		nb = nb * 10 + (*str - 48);
		str++;
	}
	str--;
	if (p == 1)
		flags->precision = nb;
	else
		flags->width = nb;
	return (str);
}

void	ft_empty_buf(t_print *lst)
{
	write(1, lst->buf, lst->i);
	lst->a = lst->a + lst->i;
	lst->i = 0;
}

void	ft_put_in_buf(char *keep, t_print *lst, t_flags *flags)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(keep);
	flags->zero = (flags->minus) ? 0 : flags->zero;
	flags->space = (flags->plus) ? 0 : flags->space;
	if (keep[0] == '-' && !flags->plus)
		lst->buf[lst->i++] = '-';
	if (flags->plus && flags->zero)
		lst->buf[lst->i++] = (keep[0] == '-') ? '-' : '+';
	if (flags->width > len && !flags->minus)
		string_width(lst, flags, flags->width - len);
	if (keep[0] == '-')
		i++;
	while (keep[i])
	{
		if (lst->i >= BUFFER_SIZE)
			ft_empty_buf(lst);
		lst->buf[lst->i++] = keep[i++];
	}
	if (flags->width && flags->minus)
		string_width(lst, flags, flags->width - len);
	free(keep);
}

void	ft_init_lst(t_flags *flags)
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
}
