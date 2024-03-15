/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:32:45 by luca              #+#    #+#             */
/*   Updated: 2024/03/14 20:49:50 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

/*int	pipex(t_mini *mini, t_node *node)
{
	int	fd[2];
	pid_t	pid;
	pid_t	pid2;

	void *res;

	if (pipe(fd) != 0)
		return(-1);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(node->cmd_path, node->cmd_matrix, NULL);
	}
	pid2 = fork();
	node = node->next;
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		execve(node->cmd_path, node->cmd_matrix, NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	return(0);
}
*/


int	pipex(t_node *node)
{
	int	i;
	int j;
	int	**fd;
	pid_t	pid;

	i = 0;
	j = 0;
	while(node[i].type == PIPE && node + i)
		i++;
	printf("array size %d\n", i);
	fd = malloc(sizeof(int *) * i);
	while(i--)
		fd[i] = malloc(sizeof(int) * 2);
	i = 0;
	while(node[i].type == PIPE)
	{
		pipe(fd[i]);
		pid = fork();
		if (pid == 0)
		{
			ft_putstr_fd("ciao", 1);
			ft_putnbr_fd(i, 1);
			if (i != 0)
				dup2(fd[i - 1][0], STDIN_FILENO);
			if (node[i].right_tkn == END_PIPE)
				dup2(fd[i][1], STDOUT_FILENO);
			while(j <= i)
			{
				close(fd[j][0]);
				close(fd[j][1]);
				j++;
			}
			execve(node[i].cmd_path, node[i].cmd_matrix, NULL);
		}
		i++;
		waitpid(-1, NULL, 0);
	}
	return(0);
}
