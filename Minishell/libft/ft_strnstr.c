/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 19:20:26 by mcamilli          #+#    #+#             */
/*   Updated: 2023/04/20 11:43:28 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hk, const char *nd, size_t len)
{
	size_t	i;
	size_t	j;

	if (nd[0] == '\0')
		return ((char *)hk);
	i = 0;
	if (len == 0)
		return (0);
	while (hk[i] && i < len)
	{
		j = 0;
		while (hk[i + j] == nd[j] && nd[j] && i + j < len)
		{
			j++;
		}
		if (nd[j] == '\0')
			return ((char *)hk + i);
		i++;
	}
	return (NULL);
}

/*int main ()
{
    const char haystack[] = "";
    const char needle[] = "";
    char *result;

    result = strnstr(haystack, needle, 0);
    printf("The substring is: %s\n", result);
   return(0);
 }*/
