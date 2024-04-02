/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:13:52 by luca              #+#    #+#             */
/*   Updated: 2024/04/02 18:50:52 by lpicciri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	execute(t_node *node, t_mini *mini)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (node->left_tkn == -2)
			close(mini->pipe_fd[0]);
		if (node->right_tkn == 222)
			close(mini->pipe_fd[1]);
		execve(node->cmd_path, node->cmd_matrix, NULL);
		perror("execve\n");
	}
}

void	set_pipes(t_mini *mini, t_node *node)
{
	int	tmp_fd;

	if (node->right_tkn == PIPE && node->left_tkn == PIPE)
	{
		tmp_fd = dup(mini->pipe_fd[0]);
		if(tmp_fd == -1)
			perror("dup\n");
		if (pipe(mini->pipe_fd) == -1)
			perror("pipes\n");
		mini->fdin = dup(tmp_fd);
		mini->fdout = mini->pipe_fd[1];
		return ;
	}
	if(node->right_tkn != END_PIPE)
		mini->fdout = mini->pipe_fd[1];
	if (node->left_tkn != START_P)
		mini->fdin = mini->pipe_fd[0];
}

void	redir_inout(t_node *node, t_mini *mini, int tmpin, int tmpout)
{
	if (node->this_tkn > 2 && node->this_tkn < 10)
	{
		if (node->this_tkn == REDIR_MAG)
			redir_mag(node, mini);
		if (node->this_tkn == REDIR_MAGMAG)
			redir_magmag(node, mini);
		if (node->this_tkn == REDIR_MIN)
			redir_min(node, mini);
		if (node->this_tkn == HERE_DOC)
			here_doc(node, mini);
	}
}

int	pipex(t_node *node, t_mini *mini)
{
	t_node *temp;
	int	tmpin;
	int	tmpout;

	errno = 0;
	temp = node;
	tmpout = dup(STDOUT_FILENO);
	tmpin = dup(STDIN_FILENO);
	redir_inout(temp, mini, tmpin, tmpout);
	if(pipe(mini->pipe_fd) == -1)
		ft_putendl_fd(strerror(errno), 2);
	while(temp)
	{
		while (temp->file != NULL)
		{
			redir_inout(temp, mini, tmpin, tmpout);
			temp = temp->next;
		}
		set_pipes(mini, temp);
		dup2(mini->fdout, STDOUT_FILENO);
		dup2(mini->fdin, STDIN_FILENO);
		execute(temp, mini);
		close(mini->fdin);
		close(mini->fdout);
		mini->fdin = dup(tmpin);
		mini->fdout = dup(tmpout);
		temp = temp->next;
	}
	if (dup2(tmpin, 0) == -1)
		ft_putendl_fd(strerror(errno), 2);
	if (dup2(tmpout, 1) == -1)
		ft_putendl_fd(strerror(errno), 2);
	close(tmpin);
	close(tmpout);
	close(mini->fdin);
	close(mini->fdout);
	while(waitpid(-1, NULL, 0) > 0);
}
