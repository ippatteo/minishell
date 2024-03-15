/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 20:15:45 by mcamilli          #+#    #+#             */
/*   Updated: 2024/03/03 18:47:34 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

//esattamente come split ma mette "*", '*', |, >>, <<, >, < 
//in stringhe diverse oltre alle parole



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

