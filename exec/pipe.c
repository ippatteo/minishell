/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:13:52 by luca              #+#    #+#             */
/*   Updated: 2024/04/04 18:42:56 by lpicciri         ###   ########.fr       */
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
	if (node->this_tkn == REDIR_MAG || node->this_tkn == REDIR_MAGMAG
		|| node->this_tkn == REDIR_MIN || node->this_tkn == HERE_DOC)
		return (0);
	return (1);
}

void	fork_exec(t_node *node, t_mini *mini)
{
	int	pid;

	if (node->this_tkn != 20)
		return (exec_builtin(node, mini));
	dup2(mini->fdout, STDOUT_FILENO);
	pid = fork();
	if (pid == 0)
	{
		close(mini->fdin);
		execve(node->cmd_path, node->cmd_matrix, NULL);
		perror("excve");
	}
}

void	set_inout(t_node *node, t_mini *mini)
{
	dup2(mini->fdin,0);
	close(mini->fdin);
	pipe(mini->pipefd);
	mini->fdin = mini->pipefd[0];
	mini->fdout = mini->pipefd[1];
	if (node->right_tkn == 222)
		mini->fdout = dup(mini->temp_out);
}

void	redir_inout(t_node *node, t_mini *mini)
{
	while(isredir(node) == 0)
	{
		if(isredir(node) == REDIR_MAG || isredir(node) == REDIR_MAGMAG)
		{
			close(mini->fdin);
			redirection_init(node, mini);
			dup2(mini->fdin, 0);
			close(mini->fdin);
		}
		if (isredir(node) == REDIR_MIN || isredir(node) == HERE_DOC)
			close(mini->fdin);
		node = node->next;
	}
	dup2(mini->fdout, 1);
	close(mini->fdout);
}


void	pipex(t_node *node, t_mini *mini)
{
	t_node	*temp;

	temp = node;
	mini->redir_flag = 0;
	mini->temp_in = dup(0);
	mini->temp_out = dup(1);
	mini->fdin = dup(mini->temp_in);
	while (temp)
	{
		if (isredir(node) == 0)
			redir_inout(temp, mini);
		set_inout(temp, mini);
		fork_exec(temp, mini);
		dup2(mini->fdout, 1);
		close(mini->fdout);
		temp = temp->next;
	}
	dup2(mini->temp_out, 1);
	close(mini->temp_out);
	dup2(mini->temp_in, 0);
	close(mini->temp_in);
	while(waitpid(-1, NULL, 0) > 0);
}
