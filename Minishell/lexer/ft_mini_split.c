/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 20:15:45 by mcamilli          #+#    #+#             */
/*   Updated: 2024/02/22 21:52:47 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

//esattamente come split ma mette "*", '*', |, >>, <<, >, < 
//in stringhe diverse oltre alle parole



char	**ft_mini_split(char *s)
{
	char	**str;
	
	if (!s)
		return (NULL);
	if ((int)count_mem(s) == -1)
		return (NULL);
	str = ft_calloc((count_mem(s) + 1), sizeof (char *));
	if (!str)
		return (NULL);
	split_mem(s, str);
	return (str);
}
