/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 20:15:45 by mcamilli          #+#    #+#             */
/*   Updated: 2024/03/19 06:34:57 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	*ft_substr0(char *s, int len)
{
	char	*s2;

	if (!s)
		return (NULL);
	s2 = (char *)ft_calloc(len + 1, sizeof(char));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, (s), len + 1);
	return (s2);
}

void swapStrings(char **str1, char **str2)
{
	char *temp = *str1;

	*str1 = *str2;
	*str2 = temp;
}

int	count_matrix(char **matrix)
{
	int	a;

	a = 0;
	while (matrix[a])
	{
		a++;
	}
	return (a);
}