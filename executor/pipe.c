/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:13:52 by luca              #+#    #+#             */
/*   Updated: 2024/03/29 15:35:53 by mcamilli         ###   ########.fr       */
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

void	pipeline_exec(int fd[2], t_node *node, t_mini *mini, bool first)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (first != true)
		{
			if (dup2(fd[0], STDIN_FILENO) == -1)
				ft_putendl_fd(strerror(errno), 2);
		}
		if (node->next != NULL)
		{
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				ft_putendl_fd(strerror(errno), 2);
		}
		close_pipe(fd, node);
		execve(node->cmd_path, node->cmd_matrix, NULL);
		ft_putendl_fd(strerror(errno), 2); //debug
	}
}

int	pipex(t_node *node, t_mini *mini)
{
	int	fd[2];
	int	pid;
	bool	first;
	t_node *temp;

	temp = node;
	first = true;
	pipe(fd);
	while(temp)
	{
		if (temp->cmd_path != NULL)
			pipeline_exec(fd, temp, mini, first);
		if (temp->next == NULL)
			break ;
		first = false;
		temp = temp->next;
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(-1, NULL, 0);
}
