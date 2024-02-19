/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 12:41:14 by mcamilli          #+#    #+#             */
/*   Updated: 2023/09/13 17:32:41 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s, char *b)
{
	int		i;
	int		t;
	char	*str;

	i = -1;
	t = 0;
	if (!s)
	{
		s = (char *) malloc(sizeof(char));
		s[0] = '\0';
	}
	str = malloc(ft_strlen(s) + ft_strlen(b) + 1);
	if (!str)
		return (NULL);
	while (s[++i])
		str[i] = s[i];
	while (b[t])
		str[i++] = b[t++];
	str[i] = '\0';
	free (s);
	return (str);
}
