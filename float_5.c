/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 20:20:17 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/12 20:26:22 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			check_validity(t_bint *int_lst, t_bint *float_lst)
{
	if (!int_lst || !float_lst)
	{
		free_lst(int_lst);
		free_lst(float_lst);
		return (0);
	}
	return (1);
}

char		*malloc_fail(t_bint *int_lst, t_bint *float_lst)
{
	free_lst(int_lst);
	free_lst(float_lst);
	return (NULL);
}

static void		floatpart_1(t_float *lst, t_bint *lst1, t_bint *lst2)
{
	int		i;

	i = lst->intexp;
	lst->mant[0] != '1' ? i++ : 1;
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
}

t_bint			*ft_floatpart(t_float *lst)
{
	t_bint		*lst1;
	t_bint		*lst2;

	if (!lst)
		return (NULL);
	lst1 = NULL;
	lst2 = NULL;
	if (!(lst1 = lst_init(lst1, 5)))
		return (NULL);
	if (!(lst2 = lst_init(lst2, 0)))
		return (free_time(NULL, lst1));
	floatpart_1(lst, lst1, lst2);
	free(lst);
	free_lst(lst1);
	return (lst2);
}
