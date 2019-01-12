/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 17:32:55 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/12 16:24:06 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int		ft_printf(const char *format, ...);

int		main(void)
{
	int		ret;
	int		tret;

	ret = 9;
	tret = 10;
//	ft_printf("aloooo %f\n", (double)123);
//	printf("mon printf = %d\n", ft_printf("%#43.7f %#43.1f\n", (double)42, (double)-42));
//	printf("vrai printf = %d\n", printf("%#43.7f %#43.1f\n", (double)42, (double)-42));
//	printf("mon printf = %d\n", ft_printf("%#.0f, %#.0f\n", (double)1, (double)-1));
//	printf("vrai printf = %d\n", printf("%#.0f, %#.0f\n", (double)1, (double)-1));
//	printf("mon printf = %d\n", ft_printf("% 43.4f, %+2.12f\n", (double)1.42, (double)1.42));
//	printf("vrai printf = %d\n", printf("% 43.4f, %+2.12f\n", (double)1.42, (double)1.42));
	printf("mon printf = %d\n", ft_printf("{% #+- 5.0f}\n", (double)0/0));
	printf("vrai printf = %d\n", printf("{% #+- 5.0f}\n", (double)0/0));
//	printf("mon printf = %d\n", ft_printf("%.15f\n", (double)-42.1));
//	printf("vrai printf = %d\n", printf("%.15f\n", (double)-42.1));
//	printf("mon printf = %d\n", ft_printf("%2.9f\n", (double)1234));
//	printf("vrai printf = %d\n", printf("%2.9f\n", (double)1234));
//	printf("mon printf = %d\n", ft_printf("%#.4f\n", (double)0xaef));
//	printf("vrai printf = %d\n", printf("%#.4f\n", (double)0xaef));
//	printf("mon printf = %d\n", ft_printf("%#9llf\n", (unsigned long long)-1248759650));
//	printf("vrai printf = %d\n", printf("%#9llf\n", (unsigned long long)-1248759650));
//	printf("mon printf = %d\n", ft_printf("%0#10.0f\n", (double)0));
//	printf("vrai printf = %d\n", printf("%0#10.0f\n", (double)0));
//	printf("mon printf = %d\n", ft_printf("%.24f\n", 12012));
//	printf("vrai printf = %d\n", printf("%.24f\n", 12012));
//	printf("mon printf = %d\n", ft_printf("test%-8f %---32f %#5.3f%#024f\n", &ret, &tret, 0x25, 0));
//	printf("vrai printf = %d\n", printf("test%-8f %---32f %#5.3f%#024f\n", &ret, &tret, 0x25, 0));
//	printf("mon printf = %d\n", ft_printf("%-4.7f\n", (double)147));
//	printf("vrai printf = %d\n", printf("%-4.7f\n", (double)147));
//	printf("mon printf = %d\n", ft_printf("osef ! %#9llf et %-12hhf\n", (double)-1248759650, (double)-1478223695));
//	printf("vrai printf = %d\n", printf("osef ! %#9llf et %-12hhf\n", (double)-1248759650, (double)-1478223695));
//	printf("mon printf = %d\n", ft_printf("%0#10.0f %0#f\n", (double)12345, (double)0));
//	printf("vrai printf = %d\n", printf("%0#10.0f %0#f\n", (double)12345, (double)0));
//	printf("mon printf = %d\n", ft_printf("test%#.4f et \n%02f \n%0#14.0f!!\n", (double)012, (double)036, (double)12587499));
//	printf("vrai printf = %d\n", printf("test%#.4f et \n%02f \n%0#14.0f!!\n", (double)012, (double)036, (double)12587499));
//	printf("mon printf = %d\n", ft_printf("cc%#.4f et %#0012f %#04hf !!", (double)0xaef, (double)0xe, (double)0));
//	printf("vrai printf = %d\n", printf("cc%#.4f et %#0012f %#04hf !!", (double)0xaef, (double)0xe, (double)0));
//	printf("mon printf = %d\n", ft_printf("%5f\n", (double)-42));
//	printf("vrai printf = %d\n", printf("%5f\n", (double)-42));

	return (0);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <float.h>

int		ft_printf(char const *format, ...);
char	*ftoa(double f, int prec);
char	*lftoa(long double f, int prec);

int		main(void)
{
	float	f;
	double	d;
	int		i;
	float	a;
	double	b;
	int		c;
	int		prec;
	int		error;
	char	buf[10000];
	char	*fstr;
	long double ld;

	a = 10000;
	b = 10000;
	c = 10000;
	srand(time(NULL));
	bzero(buf, 151);
	srand((unsigned)time(NULL));
	error = 0;
	while (i++ < 2001)
	{
		prec = rand() % 100;
		f = (float)rand()/(float)(RAND_MAX/a);
		printf("FLOAT =      %.100f with precision %d\n", f, prec);
		sprintf(buf, "%.*Lf", prec, f);
		if (strcmp((fstr = ftoa((double)f , prec)), buf))
		{
			printf("\033[31m----------ERROR----------\033[0m\n");
			printf("my printf:   %s\n", fstr);
			printf("real printf: %s\n\n", buf);
			error++;
		}
		else
			printf("\033[32m-----------OK!-----------\033[0m\n\n");
		free(fstr);
	}
	i = 0;
	while (i++ < 100)
	{
		prec = rand() % 100;
		d = (double)rand()/(double)(RAND_MAX/b);
		printf("DOUBLE =     %.100f with precision %d\n", d, prec);
		sprintf(buf, "%.*f", prec, d);
		if (strcmp((fstr = ftoa(d , prec)), buf))
		{
			printf("\033[31m----------ERROR----------\033[0m\n");
			printf("my printf:   %s\n", fstr);
			printf("real printf: %s\n\n", buf);
			error++;
		}
		else
			printf("\033[32m-----------OK!-----------\033[0m\n\n");
		free(fstr);
	}
	i = -1;
	printf("\n----------ARRONDIS----------\n");
	d = -0.0;
	while (d < 25)
	{
		i++;
		prec = i % 2 ? 0 : 1;
		sprintf(buf, "%.*f", prec, d);
		printf("DOUBLE =     %.100f with precision %d\n", d, prec);
		if (strcmp((fstr = ftoa(d , prec)), buf))
		{
			printf("\033[31m----------ERROR----------\033[0m\n");
			printf("my printf:   %s\n", fstr);
			printf("real printf: %s\n\n", buf);
			error++;
		}
		else
			printf("\033[32m-----------OK!-----------\033[0m\n\n");
		free(fstr);
		d = i * 0.25;
	}
	printf("\n----------SPECIAL CASE----------\n");
	i = -4;
	d = -0.0 / 0.0;
	while (i++ < 3)
	{
		printf("DOUBLE =     %.100f\n", d);
		sprintf(buf, "%f", d);
		if (strcmp((fstr = ftoa(d , 6)), buf))
		{
			printf("\033[31m----------ERROR----------\033[0m\n");
			printf("my printf:   %s\n", fstr);
			printf("real printf: %s\n\n", buf);
			error++;
		}
		else
			printf("\033[32m-----------OK!-----------\033[0m\n\n");
		free(fstr);
		d = i / 0.0;
	}
	f = 3.40282e+38;
	printf("MAX FLOAT =     %.100f\n", f);
	sprintf(buf, "%f", f);
	if (strcmp((fstr = ftoa(f , 6)), buf))
	{
		printf("\033[31m----------ERROR----------\033[0m\n");
		printf("my printf:   %s\n", fstr);
		printf("real printf: %s\n\n", buf);
		error++;
	}
	else
		printf("\033[32m-----------OK!-----------\033[0m\n\n");
	free(fstr);
	f = 1.17549e-38;
	printf("MIN FLOAT =     %.300f\n", f);
	sprintf(buf, "%.300f", f);
	if (strcmp((fstr = ftoa(f , 300)), buf))
	{
		printf("\033[31m----------ERROR----------\033[0m\n");
		printf("my printf:   %s\n", fstr);
		printf("real printf: %s\n\n", buf);
		error++;
	}
	else
		printf("\033[32m-----------OK!-----------\033[0m\n\n");
	free(fstr);
	d = 1.79769e+308;
	printf("MAX DOUBLE =     %.100f\n", d);
	sprintf(buf, "%f", d);
	if (strcmp((fstr = ftoa(d , 6)), buf))
	{
		printf("\033[31m----------ERROR----------\033[0m\n");
		printf("my printf:   %s\n", fstr);
		printf("real printf: %s\n\n", buf);
		error++;
	}
	else
		printf("\033[32m-----------OK!-----------\033[0m\n\n");
	free(fstr);
	d = 2.22507e-308;
	printf("MIN DOUBLE =     %.1100f\n", d);
	sprintf(buf, "%.1100f", d);
	if (strcmp((fstr = ftoa(d , 1100)), buf))
	{
		printf("\033[31m----------ERROR----------\033[0m\n");
		printf("my printf:   %s\n", fstr);
		printf("real printf: %s\n\n", buf);
		error++;
	}
	else
		printf("\033[32m-----------OK!-----------\033[0m\n\n");
	free(fstr);
	printf("MIN DOUBLE ROUND =  %.1100f\n", d);
	sprintf(buf, "%.1069f", d);
	if (strcmp((fstr = ftoa(d , 1069)), buf))
	{
		printf("\033[31m----------ERROR----------\033[0m\n");
		printf("my printf:   %s\n", fstr);
		printf("real printf: %s\n\n", buf);
		error++;
	}
	else
		printf("\033[32m-----------OK!-----------\033[0m\n\n");
	free(fstr);
	ld = LDBL_MAX;
	printf("MAX LONG DOUBLE =     %.100Lf\n", ld);
	sprintf(buf, "%Lf", ld);
	if (strcmp((fstr = lftoa(ld , 6)), buf))
	{
		printf("\033[31m----------ERROR----------\033[0m\n");
		printf("my printf:   %s\n", fstr);
		printf("real printf: %s\n\n", buf);
		error++;
	}
	else
		printf("\033[32m-----------OK!-----------\033[0m\n\n");
	free(fstr);
	ld = LDBL_MIN;
	printf("MIN LONG DOUBLE =     %.100Lf\n", ld);
	sprintf(buf, "%.7000Lf", ld);
	if (strcmp((fstr = lftoa(ld , 7000)), buf))
	{
		printf("\033[31m----------ERROR----------\033[0m\n");
		printf("my printf:   %s\n", fstr);
		printf("real printf: %s\n\n", buf);
		error++;
	}
	else
		printf("\033[32m-----------OK!-----------\033[0m\n\n");
	free(fstr);
	i = -4;
	ld = -0.0 / 0.0;
	while (i++ < 3)
	{
		printf("SPECIAL CASE LD =     %.100Lf\n", ld);
		sprintf(buf, "%Lf", ld);
		if (strcmp((fstr = lftoa(ld , 6)), buf))
		{
			printf("\033[31m----------ERROR----------\033[0m\n");
			printf("my printf:   %s\n", fstr);
			printf("real printf: %s\n\n", buf);
			error++;
		}
		else
			printf("\033[32m-----------OK!-----------\033[0m\n\n");
		free(fstr);
		ld = i / 0.0;
	}
	i = 0;
	while (i++ < 100 || !error)
	{
		prec = rand() % 100;
		ld = (long double)rand()/(long double)(RAND_MAX/c);
		printf("LONG DOUBLE =     %.100Lf with precision %d\n", ld, prec);
		sprintf(buf, "%.*Lf", prec, ld);
		fstr = lftoa(ld, prec);
		if (strcmp(fstr, buf))
		{
			printf("\033[31m----------ERROR----------\033[0m\n");
			printf("my printf:   %s\n", fstr);
			printf("real printf: %s\n\n", buf);
			error++;
		}
		else
			printf("\033[32m-----------OK!-----------\033[0m\n\n");
		free(fstr);
	}
	if (error)
		printf("\033[31m%d errors\n\033[0m", error);
	else
		printf("\033[32mno errors\033[0m\n");
	return (0);
}*/
