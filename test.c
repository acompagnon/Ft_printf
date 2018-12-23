/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 12:05:30 by acompagn          #+#    #+#             */
/*   Updated: 2018/12/23 15:48:23 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct		s_float
{
	char			mant[25];
	char			*binary;
	int				sign;
	int				intexp;
	int				intpart;
	long long		fpart;
}					t_float;

size_t		ft_strlen(const char *s)
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
		if (!(s[i + 8]))
			return (i + 8);
		i += 8;
	}
	return (i);
}

void		ft_putchar(char c)
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

int		ft_atoi_base(char *str, int str_base)
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

/*int	ft_atoi_base(char *str)
  {
  int		nb;

  while (*str)
  {
  nb = nb * 2 + (*str - '0');
  str++;
  }
  return (nb);
  }*/

void    print_bits(unsigned char octet, char *str, int *i)
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

void		ft_get_exp_mant(char *str, t_float *lst)
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

void		ft_get_point(t_float *lst)
{
	int		georges;
	int		i;
	int		j;

	i = 0;
	j = 0;
	georges = (lst->intexp - 126 <= 0) ? 0 : lst->intexp - 126;
	if (!(lst->binary = (char *)malloc(sizeof(char) * ((georges < 24) ? 26 : georges + 2))))
		return ;	
	if (georges == 0)
	{
		lst->binary[i++] = '0';
		lst->binary[i++] = '.';
		j++;
	}
	while (i < georges)
		lst->binary[i++] = (lst->mant[j]) ? lst->mant[j++] : '0';
	lst->binary[i++] = '.';
	while (lst->mant[j])
		lst->binary[i++] = lst->mant[j++];
	lst->binary[i] = 0;
	printf("binary version with point = %s\n", lst->binary);
}

int			*ft_check_ten(int *tab, int size)
{
	int		i;

	i = size;
	while (i >= 0)
	{
		if (tab[i] > 9)
		{
			tab[i - 1] += 1;
			tab[i] -= 10;
		}
		i--;
	}
	return (tab);
}

int		*ft_add(int *tab1, int *tab2, int size)
{
	int		i;
	int		j;

	i = size;
	j = 0;
	while (i >= 0)
	{
		tab2[i] = tab2[i] + tab1[i];
		i--;
	}	
	return(ft_check_ten(tab2, size));
}

int		*ft_double(int *tab, int size)
{
	int		i;

	i = size;
	while (i >= 0)
		tab[i--] *= 2;
	return(ft_check_ten(tab, size));
}

void		print_tab(int *tab, int size)
{
	int		i;
	
	i = 0;
	while (i <= size)
		printf("%d", tab[i++]);
	printf("\n");
}

void		ft_intpart(t_float *lst)
{
	int		*tab1;
	int		*tab2;
	int		i;
	int		size;

	i = 0;
	size = ft_strlen(lst->binary) / 3 + ft_strlen(lst->binary) % 3;
	if (!(tab1 = (int *)malloc(sizeof(int) * size)))
		return ;
	if (!(tab2 = (int *)malloc(sizeof(int) * size)))
		return ;
	while (i < size)
		tab1[i++] = 0;
	tab1[i] = 1;
	while (i)
		tab2[i--] = 0;
	while (lst->binary[i + 1] != '.')
		i++;
	print_tab(tab1, size);
	print_tab(tab2, size);
	while (i >= 0)
	{
		if (lst->binary[i] == '1')
			tab2 = ft_add(tab1, tab2, size);
		tab1 = ft_double(tab1, size);
		i--;
	}
	print_tab(tab2, size);
}

int			main()
{
	unsigned char	*tab;
	float			f;
	t_float			*lst;
	int				i;
	int				c;
	char			str[33];

	if (!(lst = (t_float*)malloc(sizeof(t_float))))
		return (0);
	str[32] = 0;
	i = 0;
	c = 4;
	f = 999999.123;
	tab = (unsigned char *)&f;
	while (c--)
		print_bits(*(tab + c), str, &i);
	lst->sign = (str[0] == '0') ? 1 : -1;
	ft_get_exp_mant(str, lst);
	printf("mantisse = %s\n", lst->mant);
	ft_get_point(lst);
	printf("vrai printf: %.10f\n", f);
	ft_intpart(lst);
	return (0);
}
