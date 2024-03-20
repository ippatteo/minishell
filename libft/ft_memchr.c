/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:52:32 by luca              #+#    #+#             */
/*   Updated: 2023/01/26 18:02:50 by lpicciri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*to_search;

	to_search = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (to_search[i] == (unsigned char)c)
			return ((void *)(str + i));
		i++;
	}
	return (0);
}
