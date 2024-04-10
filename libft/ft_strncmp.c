/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:07:00 by lpicciri          #+#    #+#             */
/*   Updated: 2023/02/17 14:57:38 by lpicciri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	else
	{
		while (str1[i] == str2[i] && i < n - 1)
		{
			if (str1[i] == '\0' || str2[i] == '\0')
				break ;
			i++;
		}
	}
	return ((unsigned char)(str1[i]) - (unsigned char)(str2[i]));
}
