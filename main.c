/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 17:32:55 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/10 21:56:45 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int		ft_printf(const char *format, ...);

int		main(void)
{
	int		i;
	
	i = 42;
	//ft_printf("mon printf = float precision 12: %.12f\n", 100.0123456789);
	//printf("vrai printf = float precision 12: %.12f\n", 100.0123456789);
	//printf("%d\n", ft_printf("je suis %s", "la\n"));
	//printf("%d\n", printf("je suis %s", "la\n"));
	printf("50 = mon printf = %d\n", ft_printf("{%10d}\n", -7));
	printf("50 = vrai printf = %d\n", printf("{%10d}\n", -7));
	printf("mon printf = %d\n", ft_printf("%+d\n", -42));
	printf("vrai printf = %d\n", printf("%+d\n", -42));
	printf("mon printf = %d\n", ft_printf("%o\n", 0));
	printf("vrai printf = %d\n", printf("%o\n", 0));
	printf("mon printf = %d\n", ft_printf("%#.O\n", 0));
	printf("vrai printf = %d\n", printf("%#.O\n", 0));
}
