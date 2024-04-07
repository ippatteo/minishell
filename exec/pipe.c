/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:13:52 by luca              #+#    #+#             */
/*   Updated: 2024/04/07 11:40:25 by luca             ###   ########.fr       */
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

int	redir_inout(t_node *node, t_mini *mini)
{
	if (node->this_tkn == REDIR_MIN || node->this_tkn== HERE_DOC)
	{
		close(mini->fdin);
		if (redirection_init(node, mini) == -1)
			return (-1);
		dup2(mini->fdin, 0);
		close(mini->fdin);
	}
	else if(node->this_tkn == REDIR_MAG || node->this_tkn == REDIR_MAGMAG)
	{
		close(mini->fdout);
		redirection_init(node, mini);
	}
	dup2(mini->fdout, 1);
	close(mini->fdout);
	return (0);
}

void	reset(t_mini *mini)
{
	int	status;

	status = 0;
	dup2(mini->temp_out, 1);
	close(mini->temp_out);
	dup2(mini->temp_in, 0);
	close(mini->temp_in);
	while(waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			g_exit = (WEXITSTATUS(status));
	}
}
void ft_printnode(t_node *node)
{
	t_node *tmp;
	static int i;

	tmp = node;
	if (!node)
		return;
	i = 0;
	while (tmp != NULL)
	{
		printf("node path = %s\n", tmp->cmd_path);
		printf("node left_tkn = %d\n", tmp->left_tkn);
		printf("node right_tkn = %d\n", tmp->right_tkn);
		printf("node this_tkn = %d\n", tmp->this_tkn);
		printf("node file= %s\n", tmp->file);
		printf("\n--------------------\n");
		tmp = tmp->next;
	}
}

void	pipex(t_node *node, t_mini *mini)
{
	mini->temp_in = dup(0);
	mini->temp_out = dup(1);
	mini->fdin = dup(mini->temp_in);
	while (node)
	{
		set_inout(node, mini);
		while (isredir(node) == 0)
		{
			redir_inout(node, mini);
			node = node->next;
		}
		fork_exec(node, mini);
		dup2(mini->fdout, 1);
		close(mini->fdout);
		node = node->next;
	}
	reset(mini);
}
