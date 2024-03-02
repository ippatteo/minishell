/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:07:45 by lpicciri          #+#    #+#             */
/*   Updated: 2023/02/19 18:24:27 by lpicciri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	const char	*null;

	null = s;
	i = ft_strlen(s);
	s = (s + i);
	while (*s != *null && c != *s)
		s--;
	if (c == *s)
		return ((char *)s);
	return (0);
}
