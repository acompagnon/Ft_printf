/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 18:02:42 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/07 16:50:48 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		int_aug(int p, t_bint *int_lst, t_bint *float_lst)
{
	t_bint	*curr;
	print_lst(int_lst);
	print_lst(float_lst);

	curr = int_lst;
	if ((curr->nb % 2 != 0 && float_lst->nb == 5 && p != 1) ||
		(float_lst->nb > 9) || (!p && float_lst->nb >= 5 && curr->nb % 2 != 0)
		|| (!p && float_lst->nb > 5 && curr->nb % 2 == 0))
	{
		curr->nb += 1;
		float_lst->nb = 0;
	}
	ft_check_ten(int_lst);
}

char		*ft_create_str(int p, t_bint *int_lst, t_bint *float_lst, int sign)
{
	int		size;
	int		i;
	int		j;
	t_bint	*intpart;
	char	*keep;

	size = 0;
	intpart = int_lst;
	j = 0;
	while (intpart)
	{
		size++;
		intpart = intpart->next;
	}
	i = size;
	if (!(keep = (char *)malloc(sizeof(char) * (size + (p ? p + 1 : p) + (sign ? 1 : 0)))))
		return (NULL);
	if (sign)
	{
		keep[0] = '-';
		size += 1;
		i += 1;
	}
	while (int_lst)
	{
		keep[--size] = int_lst->nb + 48;
		int_lst = int_lst->next;
	}
	if (p)
		keep[i++] = '.';
	while (j < p)
	{
		keep[i + j++] = float_lst->nb + 48;
		float_lst = float_lst->next;
	}
	return (keep);
}

char		*ft_precision(int p, t_bint *int_lst, t_bint *float_lst, int sign)
{
	t_bint	*curr;
	int		len;

	curr = float_lst;
	len = 0;
	p = (p == -1) ? 6 : p;
	while (++len < p)
	{
		if (!curr->next)
			curr->next = lst_init(curr->next, 0);
		curr = curr->next;
	}
	if (p && curr->next)
	{
		if ((curr->next->nb == 5 && (curr->next->next ||
						curr->nb % 2 != 0)) || (curr->next->nb > 5))
			curr->nb += 1;
		ft_check_float(float_lst);
	}
	if (float_lst->nb >= 5 && p <= 1)
		int_aug(p, int_lst, float_lst);
	return (ft_create_str(p, int_lst, float_lst, sign));
}

int			check_double(double f, t_float *lst)
{
	int		nan;
	int		inf;
	int		i;

	nan = (f != f ? 1 : 0);
	inf = (lst->intexp == 2047 ? 1 : 0);
	i = 0;
	if (nan || inf)
	{
		if (!(lst->keep = (char *)malloc(sizeof(char) * (4 + lst->sign))))
			return (0);
		if (lst->sign && !nan)
			lst->keep[i++] = '-';
		lst->keep[i++] = nan ? 'n' : 'i';
		lst->keep[i++] = nan ? 'a' : 'n';
		lst->keep[i++] = nan ? 'n' : 'f';
		lst->keep[i] = '\0';
		return (0);
	}
	return (1);
}
