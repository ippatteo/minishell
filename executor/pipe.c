/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:32:45 by luca              #+#    #+#             */
/*   Updated: 2024/03/20 12:32:03 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	close_pipe(t_node *node,t_pipes *pipes,int index)
{
	int	i;

	i = 0;
	while(i < index)
	{
		close(pipes->fd[i][0]);
		close(pipes->fd[i][1]);
	}
}

void	exec_pipe(t_node *node, t_pipes *pipes)
{
	int	pid;

	pipes->index = 0;
	while(node)
	{
		pipes->pid = fork();
		if (pipes->pid == 0)
		{
			if (node->left_tkn != 0)
				dup2(pipes->fd[0][0], STDIN_FILENO);
			if (node->right_tkn != END_PIPE)
				dup2(pipes->fd[0][1], STDOUT_FILENO);
			execve(node->cmd_path, node->cmd_matrix, NULL);
		}
		node = node->next;
	}
}

void	create_pipes(t_node *node, t_pipes *pipes)
{
	int	i;

	while(i < 2)
	{
		if (pipe(pipes->fd[i]) != 0)
			ft_putendl_fd(strerror(errno), 2);
		i++;
	}
}


int	pipex(t_node *node, t_mini *mini)
{
	int	i;
	int pid;
	t_pipes *pipes;
	i = 0;

	create_pipes(node, pipes);
	exec_pipe(node, pipes);
	return(0);
}
