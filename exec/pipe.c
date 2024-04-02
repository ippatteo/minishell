/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:13:52 by luca              #+#    #+#             */
/*   Updated: 2024/04/02 12:43:56 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	execute(t_node *node, t_mini *mini, int fd[2])
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (node->left_tkn == -2)
			close(fd[0]);
		if (node->right_tkn == 222)
			close(fd[1]);
		execve(node->cmd_path, node->cmd_matrix, NULL);
		perror("execve\n");
	}
}

void	set_pipes(t_mini *mini, t_node *node, int fd[2])
{
	if(node->right_tkn != END_PIPE)
		mini->fdout = fd[1];
	if (node->left_tkn != START_P)
		mini->fdin = fd[0];
}

void	redir_inout(t_node *node, t_mini *mini, int tmpin, int tmpout)
{

}

int	pipex(t_node *node, t_mini *mini)
{
	t_node *temp;
	int	tmpin;
	int	tmpout;
	int	fd[2];
	int	tmp;

	errno = 0;
	temp = node;
	tmpout = dup(STDOUT_FILENO);
	tmpin = dup(STDIN_FILENO);
	if(pipe(fd) == -1)
		ft_putendl_fd(strerror(errno), 2);
	while(temp)
	{
		set_pipes(mini, temp, fd);
		if (dup2(mini->fdout, STDOUT_FILENO) == -1)
			ft_putendl_fd("dup2", 2);
		if(dup2(mini->fdin, STDIN_FILENO) == -1)
			ft_putendl_fd("dup2", 2);
		execute(temp, mini, fd);
		if (node->next != NULL)
		{
			close(mini->fdin);
			close(mini->fdout);
			mini->fdin = dup(tmpin);
			mini->fdout = dup(tmpout);
		}
		temp = temp->next;
	}
	if (dup2(tmpin, 0) == -1)
		ft_putendl_fd(strerror(errno), 2);
	if (dup2(tmpout, 1) == -1)
		ft_putendl_fd(strerror(errno), 2);
	close(tmpin);
	close(tmpout);
	while(waitpid(-1, NULL, 0) > 0);
}
