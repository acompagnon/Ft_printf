/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 14:28:14 by acompagn          #+#    #+#             */
/*   Updated: 2019/02/27 16:05:47 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_sqrt(int nb)
{
	int i;

	i = 0;
	if (nb > 46340 * 46340)
		return (0);
	while (i * i < nb)
		i++;
	if (i * i == nb)
		return (i);
	else
		return (0);
}