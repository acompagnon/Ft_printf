/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 17:32:55 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/10 18:01:47 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int		ft_printf(const char *format, ...);

int		main(void)
{
	//ft_printf("mon printf = float precision 12: %.12f\n", 100.0123456789);
	//printf("vrai printf = float precision 12: %.12f\n", 100.0123456789);
	//printf("%d\n", ft_printf("je suis %s", "la\n"));
	//printf("%d\n", printf("je suis %s", "la\n"));
	printf("mon printf = %d\n", ft_printf("@main_ftprintf: %####0000 33..1..#00d\n", 256));
	printf("vrai printf = %d\n", printf("@main_ftprintf: %####0000 33..1..#00d\n", 256));
}
