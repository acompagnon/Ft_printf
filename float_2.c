/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 17:53:25 by acompagn          #+#    #+#             */
/*   Updated: 2019/06/19 16:36:08 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_add(t_bint *lst1, t_bint *lst2)
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

static void		ft_double(t_bint *lst1)
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

t_bint			*free_time(t_float *lst_float, t_bint *lst_bint)
{
	if (lst_float)
		free(lst_float);
	if (lst_bint)
		free_lst(lst_bint);
	return (NULL);
}

t_bint			*ft_intpart(t_float *lst)
{
	int		i;
	t_bint	*lst1;
	t_bint	*lst2;

	lst1 = NULL;
	lst2 = NULL;
	if (!(lst1 = lst_init(lst1, 1)))
		return (free_time(lst, NULL));
	if (!(lst2 = lst_init(lst2, 0)))
		return (free_time(lst, lst1));
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
	free_lst(lst1);
	return (lst2);
}

void			ft_multiply(t_bint *lst)
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
