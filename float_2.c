/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 17:53:25 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/10 17:21:43 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_add(t_bint *lst1, t_bint *lst2)
{
	t_bint	*tmp1;
	t_bint	*tmp2;

	tmp1 = lst1;
	tmp2 = lst2;
	while (tmp1)
	{
		tmp2->nb = tmp2->nb + tmp1->nb;
		tmp1 = tmp1->next;
		if (!tmp2->next && tmp1)
			tmp2->next = lst_init(tmp2, 0);
		tmp2 = tmp2->next;
	}
}

void		ft_double(t_bint *lst1)
{
	t_bint	*tmp;

	tmp = lst1;
	while (tmp)
	{
		tmp->nb *= 2;
		tmp = tmp->next;
	}
	ft_check_ten(lst1);
}

t_bint		*ft_intpart(t_float *lst)
{
	int		i;
	t_bint	*lst1;
	t_bint	*lst2;

	lst1 = lst_init(lst1, 1);
	lst2 = lst_init(lst2, 0);
	i = lst->intexp;
	while (i-- > 0)
	{
		if (i < lst->size && lst->mant[i] == '1')
		{
			ft_add(lst1, lst2);
			ft_check_ten(lst2);
		}
		ft_double(lst1);
	}
	return (lst2);
}

void		ft_multiply(t_bint *lst)
{
	t_bint		*curr;
	char		tmp;
	char		retenue;

	curr = lst;
	retenue = 0;
	while (curr)
	{
		tmp = curr->nb;
		curr->nb = curr->nb / 2 + retenue;
		retenue = (tmp % 2) * 5;
		if (!curr->next && retenue)
			curr->next = lst_init(curr->next, 0);
		curr = curr->next;
	}
}

t_bint		*ft_floatpart(t_float *lst)
{
	t_bint		*lst1;
	t_bint		*lst2;
	int			i;

	i = lst->intexp;
	lst1 = lst_init(lst1, 5);
	lst2 = lst_init(lst2, 0);
	if (lst->mant[0] != '1')
		i++;
	while (i < lst->size)
	{
		if (i >= 0 && lst->mant[i] == '1')
		{
			ft_add(lst1, lst2);
			ft_check_float(lst2);
		}
		ft_multiply(lst1);
		i++;
	}
	return (lst2);
}
