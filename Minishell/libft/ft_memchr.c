/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:40:05 by mcamilli          #+#    #+#             */
/*   Updated: 2023/04/18 18:53:06 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int d, size_t n)
{
	unsigned char	*p;
	unsigned char	c;

	c = d;
	p = (unsigned char *)s;
	while (n--)
	{
		if (*p == c)
			return (p);
		p++;
	}
	return (NULL);
}
