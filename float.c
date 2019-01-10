/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 18:01:57 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/07 16:35:55 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ftoa(double f, int p)
{
	t_float		*lst;

	if (!(lst = (t_float*)malloc(sizeof(t_float))))
		return (0);
	print_bits((unsigned char *)&f, lst);
	if (!(check_double(f, lst)))
		return (lst->keep);
	lst->intexp = lst->intexp - 1022;
	return (ft_precision(p, ft_intpart(lst), ft_floatpart(lst), lst->sign));
}

char		*lftoa(long double f, int p)
{
	t_float		*lst;

	if (!(lst = (t_float*)malloc(sizeof(t_float))))
		return (0);
	print_long((unsigned char *)&f, lst);
	printf("lst->size = %d\n", lst->size);
	printf("lst->mant = %s\n", lst->mant);
	printf("lst->exp = %d\n", lst->intexp);
	//32767 inf;
	//16382 / 1022;
	lst->intexp = lst->intexp - 16382;
	return (ft_precision(p, ft_intpart(lst), ft_floatpart(lst), lst->sign));
}

/*int		main()
{
	double	f;
	int		p;

	f = 7386.8252511074879294028505682945251464843750000000000000000000000000000000000000000000000000000000000000;
   	p = 0;
	printf("vrai printf: %.0f\n", f);
	printf("mon printf:  %s\n", ftoa(f, p));
	return (0);
}*/
