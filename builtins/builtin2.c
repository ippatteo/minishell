/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:58:58 by luca              #+#    #+#             */
/*   Updated: 2024/03/21 17:08:29 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int		ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

void ft_unset(t_mini *mini, char **mtr)
{
	int i;
	int j;

	i = 1;
	while(mtr[i])
	{
		j = 0;
		while(mini->en[j])
		{
			if(!ft_strncmp(mini->en[j], mtr[i], ft_strlen(mtr[i])))
			{
				free(mini->en[j]);
				while (mini->en[j])
				{
					mini->en[j] = mini->en[j + 1];
					j++;
				}
				break;
			}
			j++;
		}
		i++;
	}
}

void	ft_exit(t_node *node, t_mini *mini)
{
	ft_exit_all(node, mini);
	exit(0);
}
