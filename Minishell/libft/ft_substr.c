/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:26:19 by mcamilli          #+#    #+#             */
/*   Updated: 2024/02/22 09:50:51 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s2;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	s2 = (char *)ft_calloc(len + 1, sizeof(char));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, (s + start), len + 1);
	return (s2);
}

char	*ft_substr_ok(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	substr = (char *) malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	j = start;
	while (j < (start + len))
		substr[i++] = s[j++];
	substr[i] = '\0';
	return (substr);
}

int main(void)
{
	char s[] = "pippobaudo";
	int start = 3;
	size_t len = 2;
	printf("%s\n", s);
	printf("%s\n", ft_substr(s, start, len));
	printf("%s\n", ft_substr_ok(s, start, len));
	return (0);
}

