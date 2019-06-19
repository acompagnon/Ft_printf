/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acompagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:52:53 by acompagn          #+#    #+#             */
/*   Updated: 2019/03/25 19:03:27 by acompagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		abs_double(double nb)
{
	return ((nb < 0) ? -nb : nb);
}
