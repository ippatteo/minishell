/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:07:30 by mcamilli          #+#    #+#             */
/*   Updated: 2024/04/09 21:55:12 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	err_quote(t_mini *mini)
{
	int	i;

	i = -1;
	while (mini->commands[++i])
	{
		if (mini->commands[i][0] == D_QUOT || mini->commands[i][0] == QUOT)
		{
			if (!mini->commands[i][1])
				return (0);
			if (mini->commands[i][0] == D_QUOT
				&& (ft_strlen(mini->commands[i]) - 1))
			{
				if (mini->commands[i][ft_strlen (mini->commands[i]) - 1]
					!= D_QUOT)
					return (0);
			}
			else if (mini->commands[i][0] == QUOT
				&& (ft_strlen(mini->commands[i]) - 1))
			{
				if (mini->commands[i][ft_strlen(mini->commands[i]) - 1] != QUOT)
					return (0);
			}
		}
	}
	return (1);
}

int	is_there_redir(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->tkn[i])
	{
		if (mini->tkn[i] == 1)
			return (1);
		i++;
	}
	return (0);
}

void	exec_builtin(t_node *node, t_mini *mini)
{
	if (node->this_tkn == CD)
		ft_cd(node, mini);
	if (node->this_tkn == ECHO)
		ft_echo(node, mini);
	if (node->this_tkn == PWD)
		ft_pwd(node, mini);
	if (node->this_tkn == EXPORT)
		ft_export(node, mini);
	if (node->this_tkn == UNSET)
		ft_unset(mini, node->cmd_matrix);
	if (node->this_tkn == ENV)
		ft_env(node, mini);
	if (node->this_tkn == EXIT)
		ft_exit(node, mini);
}

int	ispipeline(t_node *node)
{
	t_node	*temp;

	temp = node;
	while (temp)
	{
		if (temp->left_tkn == 2)
			return (0);
		temp = temp->next;
	}
	return (1);
}

void	setup_redir(t_node *node, t_mini *mini)
{
	while(isredir(node) == 0 && node)
	{
		if (node->this_tkn == REDIR_MAG)
			redir_mag(node, mini);
		if (node->this_tkn == REDIR_MAGMAG)
			redir_magmag(node, mini);
		if (node->this_tkn == REDIR_MIN)
			redir_min(node, mini);
		if (node->this_tkn == HERE_DOC)
			here_doc(node, mini);
		node = node->next;
	}
}
