/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:03:08 by mcamilli          #+#    #+#             */
/*   Updated: 2023/04/18 18:56:28 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*tmp;
	unsigned char		*dest;

	tmp = (unsigned char *)src;
	dest = (unsigned char *)dst;
	if (!dest && !tmp)
		return (dest);
	if (dest > tmp && dest < tmp + len)
	{
		while (len-- > 0)
			dest[len] = tmp[len];
	}
	else
		while (len-- > 0)
			*dest++ = *tmp++;
	return (dst);
}
