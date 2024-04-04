/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:24:37 by luca              #+#    #+#             */
/*   Updated: 2024/04/04 18:08:35 by lpicciri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	exec(t_node *node, t_mini *mini)
{
	t_node	*temp;

	temp = node;
	if (ispipeline(temp, mini) == 0)
		return (pipex(temp, mini));
	while (temp->this_tkn > 2 && temp->this_tkn < 10)
	{
		if (node->file == NULL || !redirection_init(temp, mini))
		{
			g_exit = 2;
			ft_putendl_fd("unexpected token", 2);
			return ;
		}
		temp = temp->next;
		if (temp == NULL)
			return ;
	}
	if (temp->this_tkn > 10 && temp->this_tkn < 21)
	{
		exec_single(temp, mini);
		return ;
	}
	ft_putendl_fd("command not found", 2);
	g_exit = 127;
	return ;
}

void	ft_close_all(t_mini *mini)
{
	if (mini->fdin != STDIN_FILENO)
	{
		close(mini->fdin);
		mini->fdin = STDIN_FILENO;
	}
	if (mini->fdout != STDOUT_FILENO)
	{
		close(mini->fdout);
		mini->fdout = STDOUT_FILENO;
	}
}

void	handle(int signum)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	signal_heredoc(void)
{
	signal(SIGQUIT, handle);
	signal(SIGINT, sig_handle);
	signal(SIGTERM, sig_handle);
}
