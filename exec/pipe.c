/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:13:52 by luca              #+#    #+#             */
/*   Updated: 2024/04/09 10:31:03 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	fork_exec(t_node *node, t_mini *mini)
{
	int	pid;

	if (node->this_tkn != 20 && node->this_tkn != 111)
	{
		exec_builtin(node, mini);
		return ;
	}
	if (access(node->cmd_path, X_OK) == -1)
	{
		g_exit = 127;
		ft_putstr(node->cmd_path);
		ft_putendl_fd(" : command not found", 2);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, handle);
		close(mini->fdin);
		execve(node->cmd_path, node->cmd_matrix, NULL);
		perror("excve");
	}
}

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

void	set_inout(t_node *node, t_mini *mini)
{
	int	fd[2];

	dup2(mini->fdin, 0);
	close(mini->fdin);
	if (mini->pipeline == 1)
	{
		pipe(fd);
		mini->fdin = fd[0];
		mini->fdout = fd[1];
	}
	if (node->right_tkn == 222)
		mini->fdout = dup(mini->temp_out);
}

int	redir_inout(t_node *node, t_mini *mini)
{
	while (isredir(node) == 0 && node != NULL)
	{
		if (node->this_tkn == REDIR_MIN || node->this_tkn == HERE_DOC)
		{
			close(mini->fdin);
			if (redirection_init(node, mini) == -1)
				return (-1);
			dup2(mini->fdin, 0);
			close(mini->fdin);
		}
		else if (node->this_tkn == REDIR_MAG || node->this_tkn == REDIR_MAGMAG)
		{
			close(mini->fdout);
			redirection_init(node, mini);
		}
		node = node->next;
	}
	dup2(mini->fdout, 1);
	close(mini->fdout);
	return (0);
}

void	reset(t_mini *mini)
{
	int	status;

	dup2(mini->temp_out, 1);
	close(mini->temp_out);
	dup2(mini->temp_in, 0);
	close(mini->temp_in);
	while (waitpid(-1, &status, 0) > 0);
}

void	exec(t_node *node, t_mini *mini)
{
	mini->temp_in = dup(0);
	mini->temp_out = dup(1);
	mini->fdin = dup(mini->temp_in);
	if (ispipeline(node, mini) == 0)
		mini->pipeline = 1;
	while (node)
	{
		set_inout(node, mini);
		if (redir_inout(node, mini) == -1)
			return ;
		fork_exec(node, mini);
		node = node->next;
	}
	reset(mini);
}
