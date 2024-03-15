/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:32:45 by luca              #+#    #+#             */
/*   Updated: 2024/03/15 13:42:39 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

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
		waitpid(-1, NULL, 0);
		i++;
	}
	return(0);
}
