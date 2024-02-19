/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:45:00 by mcamilli          #+#    #+#             */
/*   Updated: 2023/09/23 15:36:09 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_type(va_list args, char str)
{
	if (str == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (str == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (str == 'p')
		return (ft_putstr("0x") + ft_esa(va_arg(args, unsigned long),
				"0123456789abcdef", 16));
	if (str == 'x')
		return (ft_esa_x(va_arg(args, unsigned int),
				"0123456789abcdef", 16));
	if (str == 'X')
		return (ft_esa_x(va_arg(args, unsigned int), "0123456789ABCDEF", 16));
	if (str == '%')
		return (ft_putchar('%'));
	if (str == 'i')
		return (ft_putnbr(va_arg(args, int)));
	if (str == 'd')
		return (ft_putnbr(va_arg(args, int)));
	if (str == 'u')
		return (ft_putnbr_u(va_arg(args, unsigned int)));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;
	int		byte;

	i = 0;
	byte = 0;
	if (!s)
		return (0);
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			while (s[i] == 32)
				i++;
			byte += ft_type(args, s[i++]);
		}
		else
			byte += ft_putchar(s[i++]);
	}
	va_end(args);
	return (byte);
}
