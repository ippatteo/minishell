/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceck_quot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:16:16 by lpicciri          #+#    #+#             */
/*   Updated: 2024/03/19 15:55:14 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void realloc_quotes(t_mini *mini)
{
	int i;
	char *tmp;

	i = 0;
	tmp = NULL;
	while (mini->commands[i])
	{
		if (mini->commands[i][0] == D_QUOT || mini->commands[i][0] == QUOT)
		{
			tmp = ft_strdup(mini->commands[i]);
			free(mini->commands[i]);
			mini->commands[i] = ft_substr(tmp, 1, ft_strlen(tmp) - 2 );
			free(tmp);
		}
		i++;
	}
}
