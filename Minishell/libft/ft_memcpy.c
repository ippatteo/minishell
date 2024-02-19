/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:02:06 by mcamilli          #+#    #+#             */
/*   Updated: 2023/09/22 14:40:20 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	char			*p;
	const char		*s;

	if (!src && !dst)
		return (0);
	p = (char *)dst;
	s = (const char *)src;
	i = 0;
	while (i < n)
	{
		p[i] = s[i];
		i++;
	}
	return (dst);
}
