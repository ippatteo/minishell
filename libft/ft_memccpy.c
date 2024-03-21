/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:40:28 by luca              #+#    #+#             */
/*   Updated: 2023/01/26 18:02:45 by lpicciri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t				i;
	const unsigned char	*temp_src;
	unsigned char		*temp_dest;

	temp_src = (const unsigned char *)src;
	temp_dest = (unsigned char *)dest;
	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		temp_dest[i] = temp_src[i];
		if (temp_src[i] == c)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
