/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 16:11:18 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/04 18:08:32 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_float
{
	char		mant[25];
	char		*binary;
	char		*keep;
	int			sign;
	int			intexp;
	int			intpart;
	long long	fpart;
}				t_float;

size_t			ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (!s[i])
			return (i);
		if (!s[i + 1])
			return (i + 1);
		if (!s[i + 2])
			return (i + 2);
		if (!s[i + 3])
			return (i + 3);
		if (!s[i + 4])
			return (i + 4);
		if (!s[i + 5])
			return (i + 5);
		if (!(s[i + 6]))
			return (i + 6);
		if (!(s[i + 7]))
			return (i + 7);
		i += 7;
	}
	return (i);
}

void			ft_putchar(char c)
{
	write(1, &c, 1);
}

static int		ft_base(char c, int base)
{
	char *base_min;
	char *base_maj;

	if (!(base_min = (char *)malloc(sizeof(char) * 17)))
		return (0);
	if (!(base_maj = (char *)malloc(sizeof(char) * 17)))
		return (0);
	base_min = "0123456789abcdef";
	base_maj = "0123456789ABCDEF";
	while (base--)
		if (base_min[base] == c || base_maj[base] == c)
			return (1);
	return (0);
}

static int		ft_value(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

int				ft_atoi_base(char *str, int str_base)
{
	int i;
	int sign;
	int nb;

	i = 0;
	sign = 1;
	nb = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (ft_base(*str, str_base))
		nb = nb * str_base + ft_value(*str++);
	return (nb * sign);
}

void			print_bits(unsigned char octet, char *str, int *i)
{
	unsigned char comp;

	comp = 128;
	while (comp)
	{
		if (octet & comp)
			str[(*i)++] = '1';
		else
			str[(*i)++] = '0';
		comp /= 2;
	}
}

void			ft_get_exp_mant(char *str, t_float *lst)
{
	char	exp[9];
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (i < 9)
		exp[j++] = str[i++];
	exp[j] = 0;
	lst->intexp = ft_atoi_base(exp, 2);
	lst->mant[0] = '1';
	j = 1;
	while (i < 32)
		lst->mant[j++] = str[i++];
	lst->mant[j] = 0;
}

void			ft_get_point(t_float *lst)
{
	int		georges;
	int		i;
	int		j;

	i = 0;
	j = 0;
	lst->intexp = lst->intexp - 126;
	georges = (lst->intexp <= 0) ? 0 : lst->intexp;
	if (!(lst->binary = (char *)malloc(sizeof(char) * (100))))
		return ;
	if (georges == 0)
		lst->binary[i++] = '0';
	while (i < georges)
		lst->binary[i++] = (lst->mant[j]) ? lst->mant[j++] : '0';
	lst->binary[i++] = '.';
	while (lst->intexp < 0)
	{
		lst->binary[i++] = '0';
		lst->intexp++;
	}
	while (lst->mant[j])
		lst->binary[i++] = lst->mant[j++];
	lst->binary[i] = 0;
}
