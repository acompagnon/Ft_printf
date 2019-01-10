/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 17:32:55 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/10 16:46:49 by acompagn         ###   ########.fr       */
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
	printf("%d\n", ft_printf("%-0#8x\n", 42));
	printf("%d\n", printf("%-0#8x\n", 42));
}
