/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:13:52 by luca              #+#    #+#             */
/*   Updated: 2024/04/02 17:43:58 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	close_pipe(int fd[2], t_node *node)
{
	if (node->next && node->this_tkn == PIPE)
		return ;
	if (node->this_tkn == PIPE)
		close(fd[1]);
	if (node->this_tkn == 0)
		close(fd[0]);
}

void	pipeline_exec(t_node *node, t_mini *mini)
{
	int	fd[2];
	int	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if (node->left_tkn != START_P)
		{
			if (dup2(fd[0], STDIN_FILENO) == -1)
				ft_putendl_fd(strerror(errno), 2);
		}
		if (node->next != NULL)
		{
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				ft_putendl_fd(strerror(errno), 2);
		}
		close(fd[1]);
		close(fd[0]);
		close(mini->temp_in);
		close(mini->temp_out);
		execve(node->cmd_path, node->cmd_matrix, NULL);
		ft_putendl_fd(strerror(errno), 2);
	}
}

int	pipex(t_node *node, t_mini *mini)
{
	int		pid;
	t_node	*temp;

	temp = node;
	while (temp)
	{
		if (temp->cmd_path != NULL)
			pipeline_exec(temp, mini);
		temp = temp->next;
	}
	dup2(mini->temp_in, 0);
	dup2(mini->temp_out, 1);
	waitpid(-1, NULL, 0);
}
