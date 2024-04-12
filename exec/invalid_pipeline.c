/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 05:42:39 by mcamilli          #+#    #+#             */
/*   Updated: 2024/04/11 14:08:40 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	valid_pipeline(t_node *node)
{
	int	p;

	p = node->n_pipe;
	while (node->n_pipe == p || node)
	{
		if (node->this_tkn > 10 && node->this_tkn <= 20)
			return (1);
		if (node->next != NULL)
			node = node->next;
		else
			break ;
	}
	ft_putendl_fd("error : no command to input!", 2);
	return (0);
}

int	ispipeline(t_node *node, t_mini *mini)
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

void	set_inout(t_node *node, t_mini *mini)
{
	int	fd[2];

	dup2(mini->fdin, STDIN_FILENO);
	close(mini->fdin);
	if (mini->pipeline == 1)
	{
		if (pipe(fd) == -1)
			perror("pipe\n");
		mini->fdin = fd[0];
		mini->fdout = fd[1];
	}
	if (node->right_tkn == 222 || mini->pipeline == 0)
		mini->fdout = dup(mini->temp_out);
}
