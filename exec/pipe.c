/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:13:52 by luca              #+#    #+#             */
/*   Updated: 2024/04/09 17:47:34 by lpicciri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ispipeline(t_node *node)
{
	t_node	*temp;

	temp = node;
	while (temp)
	{
		if (temp->left_tkn == 2)
			return (0);
		temp = temp->next;
	}
	return (1);
}

void	init_pipe(t_node *node, t_mini *mini)
{
	
}

void	exec(t_node *node, t_mini *mini)
{
	mini->temp_in = dup(0);
	mini->temp_out = dup(1);
	mini->fdin = dup(0);
	while (node)
	{
		if (ispipeline(node) == 0)
			init_pipe(node, mini);
	}
	reset(mini);
}
