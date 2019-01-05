/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 16:21:10 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/05 16:48:53 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int		ft_printf(char const *format, ...);
char	*ftoa(double f, int prec);

int		main(void)
{
	float	f;
	double	d;
	int		i;
	float	a;
	double	b;
	int		prec;
	int		error;
	char	buf[2001];
	char	*fstr;

	a = 10000;
	b = 10000;
	srand(time(NULL));
	bzero(buf, 151);
	srand((unsigned)time(NULL));
	while (i++ < 2001)
	{
		prec = rand() % 100;
		f = (float)rand()/(float)(RAND_MAX/a);
		printf("FLOAT =      %.100f with precision %d\n", f, prec);
		sprintf(buf, "%.*f", prec, f);
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
	if (error)
		printf("\033[31m%d errors\n\033[0m", error);
	else
		printf("\033[32mno errors\033[0m\n");
	return (0);
}
