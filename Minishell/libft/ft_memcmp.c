/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:33:18 by mcamilli          #+#    #+#             */
/*   Updated: 2023/04/17 13:40:30 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*sa;
	unsigned char	*sb;
	size_t			i;

	i = 0;
	sa = (unsigned char *)s1;
	sb = (unsigned char *)s2;
	while (i < n)
	{
		if (sa[i] != sb[i])
			return (sa[i] - sb[i]);
		else
			i++;
	}
	return (0);
}
