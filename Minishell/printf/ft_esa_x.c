/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_esa_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:17:25 by mcamilli          #+#    #+#             */
/*   Updated: 2023/09/22 00:37:42 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_esa_x(unsigned int k, char *f, int base)
{
	int	i;

	i = 1;
	if ((k / base) == 0)
		ft_putchar(f[k % base]);
	else
	{
		i += ft_esa(k / base, f, base);
		ft_esa(k % base, f, base);
	}
	return (i);
}
