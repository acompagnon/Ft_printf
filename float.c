/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 18:01:57 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/11 20:44:52 by acompagn         ###   ########.fr       */
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
	lst->intexp = lst->intexp - 16382;
	return (ft_precision(p, ft_intpart(lst), ft_floatpart(lst), lst->sign));
}

char	*str_capitalize(char *keep)
{
	int		i;

	i = 0;
	while (keep[i])
		keep[i] = keep[i] + 32;
	return (keep);
}

void	float_call(va_list ap, t_print *lst, t_flags *flags, char format)
{
	if (!flags->llf)
		lst->keep = ftoa(va_arg(ap, double), flags->precision);
	else
		lst->keep = lftoa(va_arg(ap, long double), flags->precision);
	if (format == 'F' && (lst->keep[1] == 'i' || lst->keep[1] == 'n'))
		lst->keep = str_capitalize(lst->keep);
	ft_put_in_buf(lst->keep, lst, flags);
}

