/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:24:37 by luca              #+#    #+#             */
/*   Updated: 2024/04/02 19:29:32 by lpicciri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	exec(t_node *node, t_mini *mini)
{
	t_node *temp;

	temp = node;
	while(temp->this_tkn > 2 && temp->this_tkn < 10)
	{
		if (node->file == NULL || !redirection_init(temp, mini))
		{
			g_exit = 2;
			ft_putendl_fd("unexpected token", 2);
			return ;
		}
		temp = temp->next;
		if (temp ==  NULL)
			return;
	}
	if (temp->this_tkn > 10 && temp->this_tkn < 21)
	{
		exec_single(temp, mini);
		return;
	}
	if (temp->left_tkn == -2)
		pipex(temp, mini);
	ft_putendl_fd("command not found", 2);
	g_exit = 127;
	return ;
}
