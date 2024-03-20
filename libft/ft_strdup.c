/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:03:49 by lpicciri          #+#    #+#             */
/*   Updated: 2023/01/26 18:04:18 by lpicciri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*str_allocated;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(str);
	str_allocated = malloc(len + 1);
	if (!str_allocated)
		return (NULL);
	while (str[i] != '\0')
	{
		str_allocated[i] = str[i];
		i++;
	}
	str_allocated[i] = '\0';
	return (str_allocated);
}
