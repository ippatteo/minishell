/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:58:58 by luca              #+#    #+#             */
/*   Updated: 2024/04/03 18:20:22 by lpicciri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

void	ft_unset(t_mini *mini, char **mtr)
{
	int	i;
	int	j;

	i = 1;
	while (mtr[i])
	{
		j = 0;
		while (mini->en[j])
		{
			if (!ft_strncmp(mini->en[j], mtr[i], ft_strlen(mtr[i])))
			{
				free(mini->en[j]);
				while (mini->en[j + 1])
				{
					mini->en[j] = mini->en[j + 1];
					j++;
				}
				mini->en[j] = NULL;
				break ;
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

int	check_space(char *str, t_node *node, t_mini *mini)
{
	if (str[0] == '=')
	{
		ft_putendl_fd("Invalid export variable", 2);
		g_exit = 1;
		return (1);
	}
	return (0);
}
