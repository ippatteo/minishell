/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:28:23 by mcamilli          #+#    #+#             */
/*   Updated: 2023/04/25 11:45:24 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len(int n)
{
	int	p;
	int	c;

	p = 0;
	c = 1;
	if (n < 0)
	{
		p = 1;
		n = n * -1;
	}
	while (n > 9)
	{
		c++;
		n = n / 10;
	}
	return (c + p);
}

char	*ft_itoa(int n)
{
	int		l;
	char	*s;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	l = len(n) - 1;
	s = ft_calloc(l + 2, sizeof(char));
	if (!s)
		return (NULL);
	s[l + 1] = '\0';
	if (n < 0)
	{
		n = n * -1;
		s[0] = 45;
	}
	while (n != 0 || (n == 0 && l == 0 && s[0] != 45))
	{
		s[l] = 48 + n % 10;
		n = n / 10;
		l--;
	}
	return (s);
}
