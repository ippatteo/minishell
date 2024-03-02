/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:39:16 by luca              #+#    #+#             */
/*   Updated: 2023/01/31 15:37:11 by lpicciri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_counter(int n)
{
	int			i;
	long int	num;

	num = n;
	i = 1;
	if (num < 0)
	{
		num *= -1;
		i++;
	}
	while (num > 9)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*string;
	long int	num;
	int			len;
	int			i;

	num = (long int)n;
	len = ft_counter(n);
	i = len - 1;
	string = malloc(sizeof(char) * len + 1);
	if (!string)
		return (NULL);
	string[len] = '\0';
	if (num < 0)
	{
		string[0] = '-';
		num *= -1;
	}
	while (i >= 0 && string[i] != '-')
	{
		string[i] = (num % 10) + '0';
		num /= 10;
		i--;
	}
	return (string);
}
