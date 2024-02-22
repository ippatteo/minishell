/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:00:17 by mcamilli          #+#    #+#             */
/*   Updated: 2024/02/22 09:23:23 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *source, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(source);
	if (n > 0)
	{
		while (source[i] && i < (n - 1))
		{
			dest[i] = source[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (j);
}
