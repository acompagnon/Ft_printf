/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:17:06 by acompagn          #+#    #+#             */
/*   Updated: 2018/12/17 16:20:13 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_itoa_base(uintmax_t a, char *base)
{
	unsigned long long	len;
	unsigned long long	tmp;
	unsigned long long	base_len;
	char				*keep;

	len = 1;
	tmp = a;
	base_len = ft_strlen(base);
	while (a /= base_len)
		len++;
	if (!(keep = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	keep[len] = '\0';
	while (len--)
	{
		keep[len] = base[tmp % base_len];
		tmp /= base_len;
	}
	return (keep);
}

char		*ft_decimal_itoa(intmax_t nb)
{
	int				len;
	uintmax_t		tmp;
	uintmax_t		abs;
	char			*keep;

	len = 1;
	abs = (nb < 0) ? -nb : nb;
	tmp = abs;
	while (abs /= 10)
		len++;
	if (nb < 0)
		len++;
	if (!(keep = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	keep[len] = '\0';
	if (nb < 0)
		keep[0] = '-';
	while (len-- > (nb < 0) ? 1 : 0)
	{
		keep[len] = (tmp % 10) + 48;
		tmp /= 10;
	}
	return (keep);
}

char		*ft_octal(uintmax_t a, char *keep)
{
	char	*base;

	base = "01234567\0";
	keep = ft_itoa_base(a, base);
	return (keep);
}

char		*ft_hexadecimal(intmax_t a, const char *format)
{
	char	*base;
	char	*keep;

	base = (*format == 'x') ? "0123456789abcdef\0" : "0123456789ABCDEF\0";
	keep = ft_itoa_base(a, base);
	return (keep);
}

char		*ft_itoa_addr(uintmax_t a)
{
	int				len;
	uintmax_t		tmp;
	char			*keep;
	char			*base;

	len = 3;
	tmp = a;
	base = "0123456789abcdef\0";
	while (a /= 16)
		len++;
	if (!(keep = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	keep[len] = '\0';
	keep[0] = '0';
	keep[1] = 'x';
	while (len-- > 2)
	{
		keep[len] = base[tmp % 16];
		tmp /= 16;
	}
	return (keep);
}
