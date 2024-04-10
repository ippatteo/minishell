/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:38:22 by mcamilli          #+#    #+#             */
/*   Updated: 2024/04/10 18:36:59 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"


valid_redir(t_mini *mini)
{
	int i;

	i = 0;
	while(mini->tkn)
	{
		if (mini->tkn[i] <= HERE_DOC && mini->tkn[i] >= REDIR_MIN)
		{
			if (!mini->tkn[i + 1] || mini->tkn[i + 1] == PIPE)
			{
				g_exit = 2;
				ft_putendl_fd("unexpected token\n", 2);
				return(0);
			}
		}
		return (1);
	}
}