/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 20:15:45 by mcamilli          #+#    #+#             */
/*   Updated: 2024/04/02 23:19:29 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	**ft_mini_split(t_mini *mini, char *s)
{
	char	**str;

	if (!s)
		return (NULL);
	if ((int)count_mem(mini, s) == -1)
		return (NULL);
	str = ft_calloc((count_mem(mini, s) + 1), sizeof (char *));
	if (!str)
		return (NULL);
	split_mem(mini, s, str);
	return (str);
}
