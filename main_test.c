/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 16:37:02 by acompagn          #+#    #+#             */
/*   Updated: 2019/01/04 16:41:26 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int		ft_printf(char const *format, ...);
char	*ftoa(float f, int prec);

int		main(void)
{
	float	f;
	double	d;
	int		i;
	float	a;
	double	b;
	int		prec;
	int		error;
	char	buf[151];
	char	*fstr;

	a = 101.0;
	b = 101.0;
	srand(time(NULL));
	bzero(buf, 151);
	srand((unsigned long)time(NULL));
	while (i++ < 100)
	{
		prec = rand() % 20;
		f = (float)rand()/(float)(RAND_MAX/a);
		printf("FLOAT =      %.100f with precision %d\n", (float)f, prec);
		sprintf(buf, "%.*f", prec, (float)f);
		if (strcmp((fstr = ftoa((float)f , prec)), buf))
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
		prec = rand() % 20;
		d = (float)rand()/(float)(RAND_MAX/b);
		printf("DOUBLE =     %.100f with precision %d\n", (float)d, prec);
		sprintf(buf, "%.*f", prec, (float)d);
		if (strcmp((fstr = ftoa((float)d , prec)), buf))
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
	printf("\n----------SPECIAL CASE----------\n");
	d = 0.0 / 0.0;
	printf("my printf:    %s\n", fstr = ftoa((float)d, 6));
	printf("real printf:  %.f\n\n", (float)d);
	free(fstr);
	d = 1.0 / 0.0;
	printf("my printf:    %s\n", fstr = ftoa((float)d, 6));
	printf("real printf:  %.f\n\n", (float)d);
	free(fstr);
	d = -0.0 / 0.0;
	printf("my printf:    %s\n", fstr = ftoa((float)d, 6));
	printf("real printf:  %.f\n\n", (float)d);
	free(fstr);
	d = -1.0 / 0.0;
	printf("my printf:    %s\n", fstr = ftoa((float)d, 6));
	printf("real printf:  %.f\n\n", (float)d);
	free(fstr);
	if (error)
		printf("\033[31m%d errors\n\033[0m", error);
	else
		printf("\033[32mno errors\033[0m\n");
	return (0);
}
