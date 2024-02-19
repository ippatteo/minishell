/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_esa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:14:42 by mcamilli          #+#    #+#             */
/*   Updated: 2023/09/22 00:37:45 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_esa(long unsigned k, char *f, int base)
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
