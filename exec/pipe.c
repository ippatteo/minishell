/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:13:52 by luca              #+#    #+#             */
/*   Updated: 2024/04/11 14:09:06 by mcamilli         ###   ########.fr       */
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
		ft_putstr_fd(node->cmd_path, 2);
		ft_putendl_fd(" : command not found", 2);
		return ;
	}
	pid = fork();
	if (pid == -1)
		perror("pid\n");
	if (pid == 0)
	{
		close(mini->fdin);
		execve(node->cmd_path, node->cmd_matrix, NULL);
		perror("excve");
	}
}

int	redir_inout(t_node *node, t_mini *mini)
{
	if (node->this_tkn == REDIR_MIN || node->this_tkn == HERE_DOC)
	{
		if (redirection_init(node, mini) == -1)
			return (-1);
	}
	else if (node->this_tkn == REDIR_MAG || node->this_tkn == REDIR_MAGMAG)
	{
		close(mini->fdout);
		redirection_init(node, mini);
	}
	dup2(mini->fdout, STDOUT_FILENO);
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
	while (waitpid(-1, &status, 0) > 0)
	{
	}
}

void	signal_heredoc(void)
{
	signal(SIGTERM, handle_c);
	signal(SIGINT, handle_d);
}

void	exec(t_node *node, t_mini *mini)
{
	mini->temp_in = dup(STDIN_FILENO);
	mini->temp_out = dup(STDOUT_FILENO);
	mini->fdin = dup(mini->temp_in);
	mini->fdout = dup(mini->temp_out);
	mini->pipeline = 0;
	if (ispipeline(node, mini) == 0)
		mini->pipeline = 1;
	signal_heredoc();
	while (node)
	{
		set_inout(node, mini);
		while (node)
		{
			redir_inout(node, mini);
			if (node->this_tkn == 111
				|| (node->this_tkn < 21 && node->this_tkn > 10))
				break ;
			node = node->next;
		}
		if (!node)
			return ;
		fork_exec(node, mini);
		node = node->next;
	}
	reset(mini);
}
