/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:24:37 by luca              #+#    #+#             */
/*   Updated: 2024/04/02 17:44:11 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_close_all(t_mini *mini)
{
	if (mini->curr_input != STDIN_FILENO)
	{
		close(mini->curr_input);
		mini->curr_input = STDIN_FILENO;
	}
	if (mini->curr_output != STDOUT_FILENO)
	{
		close(mini->curr_output);
		mini->curr_output = STDOUT_FILENO;
	}
}

void	exec(t_node *node, t_mini *mini)
{
	t_node	*temp;

	temp = node;
	while (temp->this_tkn > 2 && temp->this_tkn < 10)
	{
		if (node->file == NULL || !redirection_init(temp, mini))
		{
			g_exit = 2;
			ft_putendl_fd("unexpected token", 2);
			return ;
		}
		temp = temp->next;
		if (temp == NULL)
			return ;
	}
	if (temp->this_tkn > 10 && temp->this_tkn < 21)
	{
		exec_single(temp, mini);
		return ;
	}
	ft_putendl_fd("command not found", 2);
	g_exit = 127;
	return ;
}
