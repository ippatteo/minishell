/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:51:50 by mcamilli          #+#    #+#             */
/*   Updated: 2023/05/14 18:11:31 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_u(unsigned int n)
{
	int	i;

	i = 1;
	if (n <= 9)
	{
		ft_putchar(n + 48);
	}
	else
	{
		i += ft_putnbr(n / 10);
		ft_putchar(48 + n % 10);
	}
	return (i);
}
