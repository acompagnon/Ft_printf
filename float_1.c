/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 17:52:10 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/11 14:54:31 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			print_bits(unsigned char *c, t_float *lst)
{
	int 	k;
	int 	j;
	int		i;

	i = 0;
	j = 6;
	k = 4;
	lst->sign = (*(c + 7) & 128 ? 1 : 0);
	lst->intexp = ((*(c + 7) & ~128) << 4) | *(c + 6) >> 4;
	lst->mant[i++] = lst->intexp ? '1' : '0';
	while (k--)
		lst->mant[i++] = (*(c + 6) & 1 << k) ? '1' : '0';
	while (j--)
	{
		k = 8;
		while (k--)
			lst->mant[i++] = (*(c + j) & 1 << k) ? '1' : '0';
	}
	lst->mant[i] = '\0';
	lst->size = (lst->intexp ? i : (i - 1));
}

t_bint		*lst_init(t_bint *lst, char nb)
{
	if (!(lst = (t_bint *)malloc(sizeof(t_bint))))
		return (NULL);
	lst->nb = nb;
	lst->next = NULL;
	return (lst);
}

void		ft_check_ten(t_bint *lst)
{
	t_bint	*curr;

	curr = lst;
	while (curr)
	{
		if (curr->nb > 9)
		{
			if (!curr->next)
				curr->next = lst_init(curr->next, 0);
			curr->nb -= 10;
			curr = curr->next;
			curr->nb += 1;
		}
		else
			curr = curr->next;
	}
}

void		ft_check_float(t_bint *lst)
{
	int		restart;
	t_bint	*curr;

	restart = 1;
	while (restart)
	{
		curr = lst;
		restart = 0;
		while (curr->next)
		{
			if (curr->next->nb > 9)
			{
				curr->nb += 1;
				curr->next->nb -= 10;
				restart = 1;
			}
			curr = curr->next;
		}
	}
}
