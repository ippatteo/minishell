/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:13:52 by luca              #+#    #+#             */
/*   Updated: 2024/04/10 12:35:55 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	set_pipes(t_node *node, t_mini *mini)
{
	if (mini->redir_flg_output == 1)
		dup2(mini->pipefd[1], STDOUT_FILENO);
	close(mini->pipefd[1]);
	mini->fdin = mini->pipefd[0];
}

int	check_builtin(t_node *node, t_mini *mini)
{
	if (isbuiltin(node) == 1)
	{
		close(mini->fdin);
		if (node->right_tkn != 222)
			set_pipes(node, mini);
		exec_builtin(node, mini);
		return (1);
	}
	else if (isbuiltin(node) == 2)
	{
		close(mini->fdin);
		if (node->right_tkn != 222)
			set_pipes(node, mini);
		exec_builtin(node, mini);
		return (1);
	}
	return (0);
}

void	parent(t_node *node, t_mini *mini)
{
	close(mini->fdin);
	if (node->right_tkn == 222)
	{
		while(waitpid(-1, NULL, 0) > 0);
	}
	else
	{
		close(mini->pipefd[1]);
		mini->fdin = mini->pipefd[0];
	}
}

void	child(t_node *node, t_mini *mini)
{
	if (node->right_tkn != 222)
	{
		if (mini->redir_flg_output == 0)
			dup2(mini->pipefd[1], STDOUT_FILENO);
		close(mini->pipefd[1]);
		close(mini->pipefd[0]);
	}
	if (access(node->cmd_path, X_OK) == 0)
	{
		if (mini->redir_flg_input == 0)
			dup2(mini->fdin, STDIN_FILENO);
		close(mini->fdin);
		execve(node->cmd_path, node->cmd_matrix, NULL);
		perror("execve\n");
		exit(1);
	}
	else
	{
		printf("%s : command not found\n", node->cmd_path);
		exit(127);
	}
	exit(1);
}

void	execution(t_node *node, t_mini *mini)
{
	int	pid;

	pid = 0;
	if (ispipeline(node) == 0)
			pipe(mini->pipefd);
	setup_redir(node, mini);
	if (check_builtin(node, mini) == 1)
		return ;
	pid = fork();
	if (pid == 0)
		child(node, mini);
	if (pid)
		parent(node, mini);
}

void	exec(t_node *node, t_mini *mini)
{
	mini->temp_in = dup(STDIN_FILENO);
	mini->temp_out = dup(STDOUT_FILENO);
	mini->fdin = dup(STDIN_FILENO);
	while (node)
	{
		execution(node,mini);
		dup2(mini->temp_in, STDIN_FILENO);
		dup2(mini->temp_out, STDOUT_FILENO);
		node = node->next;
	}
	close(mini->temp_in);
	close(mini->temp_out);
}
