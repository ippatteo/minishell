/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:07:07 by mcamilli          #+#    #+#             */
/*   Updated: 2023/09/22 12:34:48 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	srch(char const *s1, char const *s2)
{
	int	i;
	int	t;

	t = 0;
	i = 0;
	while (s1[i] != '\0')
	{
		while (s2[t] != '\0')
		{
			if (s1[i] == s2[t])
				break ;
			t++;
		}
		if (s2[t] == '\0')
			return (i);
		i++;
		t = 0;
	}
	return (-1);
}

int	rsrch(char const *s1, char const *s2)
{
	int	i;
	int	t;

	t = 0;
	i = (int)ft_strlen(s1) - 1;
	while (i >= 0)
	{
		while (s2[t] != '\0')
		{
			if (s1[i] == s2[t])
			{
				t++;
				break ;
			}
		}
		if (s2[t] == '\0')
			return (i);
		i--;
		t = 0;
	}
	return (-1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s3;
	size_t	i;
	size_t	len;
	size_t	cazzo;

	if (!s1 || !set)
		return (NULL);
	if (srch(s1, set) == -1)
		return (ft_strdup(""));
	i = srch(s1, set);
	len = rsrch(s1, set);
	s3 = (char *)malloc((len - i + 2) * sizeof(char));
	if (!s3)
	{
		return (NULL);
		cazzo = 0;
	}
	while (i <= len)
	{
		s3[cazzo] = s1[i];
		i++;
		cazzo++;
	}
	s3[cazzo] = '\0';
	return (s3);
}
