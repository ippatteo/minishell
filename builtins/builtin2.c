/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:58:58 by luca              #+#    #+#             */
/*   Updated: 2024/04/11 19:03:43 by mcamilli         ###   ########.fr       */
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
	g_exit = 0;
}

void	ft_free_and_exit(t_node *node, t_mini *mini, int n)
{
	ft_exit_all(node, mini);
	exit(n);
}

void	ft_exit(t_node *node, t_mini *mini)
{
	int	i;

	i = 0;
	if (!node->cmd_matrix[1])
		ft_free_and_exit(node, mini, g_exit);
	while (node->cmd_matrix[i])
		i++;
	if (i > 2)
	{
		write(2, "exit: too many arguments\n", 25);
		ft_free_and_exit(node, mini, 127);
		return ;
	}
	if (i == 2)
	{
		if (node->cmd_matrix[1][0] == 48 && !node->cmd_matrix[1][1])
			ft_free_and_exit(node, mini, 0);
		if (ft_atoi(node->cmd_matrix[1]) == 0)
		{
			write(2, "exit error\n", 11);
			ft_free_and_exit(node, mini, 127);
		}
		else
			ft_free_and_exit(node, mini, (u_char)atoi(node->cmd_matrix[1]));
	}
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
