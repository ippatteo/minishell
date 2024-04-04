/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:13:52 by luca              #+#    #+#             */
/*   Updated: 2024/04/04 05:50:27 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ispipeline(t_node *node, t_mini *mini)
{
	t_node	*temp;

	temp = node;
	while (temp)
	{
		if (temp->left_tkn == -2)
			return (0);
		temp = temp->next;
	}
	return (1);
}

int	isredir(t_node *node)
{
	if (node->this_tkn == REDIR_MAG || node->this_tkn == REDIR_MAGMAG || node->this_tkn == REDIR_MIN || node->this_tkn == HERE_DOC)
		return (0);
	return (1);
}

void	fork_exec(t_node *node, t_mini *mini)
{
	int	pid;

	dup2(mini->fdout, STDOUT_FILENO);
	dup2(mini->fdin, STDIN_FILENO);
	if (ft_is_builtin(node->cmd_path))
		return(exec_builtin(node, mini));
	pid = fork();
	if (pid == 0)
	{
		if (node->left_tkn == -2)
			close(mini->pipefd[0]);
		if (node->left_tkn == 222)
			close(mini->pipefd[1]);
		execve(node->cmd_path, node->cmd_matrix, NULL);
		perror("excve");
	}
}

void	set_inout(t_node *node, t_mini *mini)
{
	int	tmp_fd;

	tmp_fd = dup(STDIN_FILENO);
	if (node->right_tkn == PIPE && node->left_tkn == PIPE)
	{
		if (dup2(tmp_fd, mini->pipefd[0]) == -1)
			perror("dup\n");
		pipe(mini->pipefd);
		dup2(tmp_fd, mini->fdin);
		mini->fdout = mini->pipefd[1];
		return ;
	}
	if(node->right_tkn != END_PIPE)
		mini->fdout = mini->pipefd[1];
	if (node->left_tkn != START_P)
		mini->fdin = mini->pipefd[0];
}

void	restore_fd(t_mini *mini)
{
	// close(mini->pipefd[0]);
	// close(mini->pipefd[1]);
	close(mini->fdin);
	close(mini->fdout);
	mini->fdin = dup(mini->temp_in);
	mini->fdout = dup(mini->temp_out);
}

void	pipex(t_node *node, t_mini *mini)
{
	t_node	*temp;
	temp = node;
	int	status;

	errno = 0;
	mini->redir_flag = 0;
	mini->temp_in = dup(STDIN_FILENO);
	mini->temp_out = dup(STDOUT_FILENO);
	status = 0;
	pipe(mini->pipefd);
	while (temp)
	{
		while (isredir(temp) == 0)
		{
			if (redirection_init (temp, mini) == 0)
				break;
			mini->redir_flag = 0;
			temp = temp->next;
		}
		set_inout(temp, mini);
		fork_exec(temp, mini);
		restore_fd(mini);
		temp = temp->next;
	}
	dup2(mini->temp_in, 0);
	dup2(mini->temp_out, 1);
	close(mini->fdin);
	close(mini->fdout);
	while(waitpid(-1, NULL, 0) > 0);
}
