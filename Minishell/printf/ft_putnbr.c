/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:49:07 by mcamilli          #+#    #+#             */
/*   Updated: 2023/05/14 18:10:53 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	int	i;

	i = 1;
	if (n == -2147483648)
	{
		return (ft_putstr("-2147483648"));
	}
	else if (n < 0)
	{
		ft_putstr("-");
		return (ft_putnbr(-n) + 1);
	}
	else if (n >= 0 && n <= 9)
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
