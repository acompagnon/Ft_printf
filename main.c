/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 17:32:55 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/04 18:10:48 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int		ft_printf(const char *format, ...);

int		main(void)
{
	printf("float precision base: %f\n", 100.0123456789);
	printf("float precision 1: %.1f\n", 100.0123456789);
	printf("float precision 2: %.2f\n", 100.0123456789);
	printf("float precision 3: %.3f\n", 100.0123456789);
	printf("float precision 4: %.4f\n", 100.0123456789);
	printf("float precision 5: %.5f\n", 100.0123456789);
	printf("float precision 6: %.6f\n", 100.0123456789);
	printf("float precision 7: %.7f\n", 100.0123456789);
	printf("float precision 8: %.8f\n", 100.0123456789);
	printf("float precision 9: %.9f\n", 100.0123456789);
	printf("float precision 10: %.10f\n", 100.0123456789);
	printf("float precision 11: %.11f\n", 100.0123456789);
	printf("float precision 12: %.12f\n", 100.0123456789);
	printf("float precision 13: %.13f\n", 100.0123456789);
	printf("float precision 14: %.14f\n", 100.0123456789);
	printf("float precision 15: %.15f\n", 100.0123456789);
	printf("float precision 16: %.16f\n", 100.0123456789);
	printf("float precision 17: %.17f\n", 100.0123456789);
	printf("float precision 18: %.18f\n", 100.0123456789);
	printf("float precision 19: %.19f\n", 100.0123456789);
	printf("float precision 20: %.20f\n", 100.0123456789);
	printf("float precision 21: %.21f\n", 100.0123456789);
	printf("float precision 22: %.22f\n", 100.0123456789);
	printf("float precision 23: %.23f\n", 100.0123456789);
	printf("float precision 24: %.24f\n", 100.0123456789);
	printf("float precision 25: %.25f\n", 100.0123456789);
	printf("float precision 26: %.26f\n", 100.0123456789);
	printf("float precision 27: %.27f\n", 100.0123456789);
	printf("float precision 28: %.28f\n", 100.0123456789);
}
