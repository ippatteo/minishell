/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:42:15 by lpicciri          #+#    #+#             */
/*   Updated: 2024/04/02 19:55:36 by lpicciri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	g_exit;

void	ft_exit_all(t_node *node, t_mini *mini)
{
	free_matrix(mini->en);
	if (mini->tkn)
		free (mini->tkn);
	if (mini->commands != NULL)
	{
		free_matrix(mini->commands);
	}
	if (node != NULL)
		ft_free_tnodes(node);
}

void	sig_handle(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_handler(void)
{
	signal(SIGINT, sig_handle);
	signal(SIGQUIT, SIG_IGN);
}

void	init_mini(t_mini *mini)
{
	mini->tmp = NULL;
	mini->commands = NULL;
	mini->tkn = NULL;
	mini->curr_input = 0;
	mini->curr_output = 1;
	mini->temp_in = dup(0);
	mini->temp_out = dup(1);
	mini->tknflag = 0;
	g_exit = 0;
}

int	main(int argc, char **argv, char **env)
{
	char		*cmd;
	t_mini		mini;
	t_node		*node;

	node = NULL;
	cmd = NULL;
	inits(argv, argc, &mini, env);
	while (1)
	{
		cmd = readline(CRED "minishell$ " RESET);
		if (cmd == NULL)
		{
			ft_exit_all(node, &mini);
			return (0);
		}
		if (*cmd != 0)
		{
			lexer(&mini, cmd);
			fill_nodes(&node, &mini);
			add_history(cmd);
		}
	}
	return (0);
}
