/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 18:01:57 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/11 14:54:11 by acompagn         ###   ########.fr       */
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
	if (!(check_long_double(f, lst)))
		return (lst->keep);
	//32767 inf;
	//16382 / 1022;
	lst->intexp = lst->intexp - 16382;
	return (ft_precision(p, ft_intpart(lst), ft_floatpart(lst), lst->sign));
}

