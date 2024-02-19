/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:00:07 by mcamilli          #+#    #+#             */
/*   Updated: 2023/04/20 15:34:11 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char	*str1, int ch)
{
	char	c;
	int		d;
	char	*str;

	str = (char *)str1;
	if ((str[0] == 0) && (ch == 0))
		return (str);
	if ((str[0] == 0) && (ch != 0))
		return (NULL);
	d = ft_strlen(str) - 1;
	c = ch;
	if (ch == 0)
		return ((str + d + 1));
	while ((str[d] != c) && (d != 0))
		d--;
	if (d != 0)
		return ((str + d));
	else if (str[0] == c)
		return (str);
	else
		return (NULL);
}
