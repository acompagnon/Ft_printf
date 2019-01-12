/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 18:02:42 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/12 20:26:25 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	int_aug(int p, t_bint *int_lst, t_bint *float_lst)
{
	t_bint	*curr;

	curr = int_lst;
	if (float_lst->nb > 9)
	{
		curr->nb += 1;
		float_lst->nb = 0;
	}
	else if (curr->nb % 2 != 0 && ((p != 1 && float_lst->nb == 5) ||
			(!p && float_lst->nb >= 5)))
	{
		curr->nb += 1;
		float_lst->nb = 0;
	}
	else if (!p && curr->nb % 2 == 0)
	{
		if (float_lst->nb > 5 || ((float_lst->nb == 5 && float_lst->next)
		&& (float_lst->next->nb > 0 || (float_lst->next->nb == 0 &&
		float_lst->next->next))))
		{
			curr->nb += 1;
			float_lst->nb = 0;
		}
	}
	ft_check_ten(int_lst);
}

int			lst_size(t_bint *lst)
{
	int		size;
	t_bint	*curr;

	size = 0;
	curr = lst;
	while (curr)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}

static char	*fill_str(t_bint *float_lst, char *keep, int p, int i)
{
	int		j;
	t_bint	*tmp;

	tmp = float_lst;
	j = 0;
	p ? keep[i++] = '.' : 1;
	while (j < p)
	{
		keep[i + j++] = float_lst->nb + 48;
		float_lst = float_lst->next;
	}
	keep[i + j] = '\0';
	free_lst(tmp);
	return (keep);
}

static char	*ft_create_str(int p, t_bint *int_lst, t_bint *float_lst, int sign)
{
	int		size;
	int		malloc_size;
	int		i;
	char	*keep;
	t_bint	*tmp;

	size = lst_size(int_lst);
	i = size;
	malloc_size = size + (p ? p + 1 : p) + sign + 1;
	tmp = int_lst;
	if (!(keep = (char *)malloc(sizeof(char) * malloc_size)))
		return (malloc_fail(int_lst, float_lst));
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
	free_lst(tmp);
	return (fill_str(float_lst, keep, p, i));
}

char		*ft_precision(int p, t_bint *int_lst, t_bint *float_lst, int sign)
{
	t_bint	*curr;
	int		len;

	if (!(check_validity(int_lst, float_lst)))
		return (NULL);
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
	if ((float_lst->nb >= 5 && p <= 1) || float_lst->nb > 9)
		int_aug(p, int_lst, float_lst);
	return (ft_create_str(p, int_lst, float_lst, sign));
}
