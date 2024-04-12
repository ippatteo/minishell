/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:01:23 by luca              #+#    #+#             */
/*   Updated: 2024/04/11 13:58:24 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	fill_redir0(t_node *new, t_mini *mini, int i, int p)
{
	set_values_as_null(new);
	new->this_tkn = mini->tkn[i];
	if (mini->tkn[i + 1] && mini->tkn[i + 1] != PIPE)
		mini->tkn[i + 1] = 1;
	else
	{
		new->error = 2;
		return ;
	}
	new->right_tkn = mini->tkn[i + 1];
	new->n_pipe = p;
	new->file = ft_strdup(mini->commands[i +1]);
}

void	fill_redir(t_node **node, t_mini *mini, int p)
{
	int		i;
	int		z;
	t_node	*new;

	i = go_int(mini, p);
	z = 0;
	while (mini->tkn[i] && mini->tkn[i] != PIPE)
	{
		if (mini->tkn[i] <= HERE_DOC && mini->tkn[i] >= REDIR_MIN)
		{
			new = (t_node *)ft_calloc(sizeof(t_node), 1);
			fill_redir0(new, mini, i, p);
			ft_lstadd_back(node, new);
		}
		i++;
	}
}

void	ft_free_tnodes(t_node *node)
{
	t_node	*temp;

	if (node == NULL)
		return ;
	while (node != NULL)
	{
		temp = node;
		node = node->next;
		if (temp->cmd_matrix != NULL)
			free_matrix(temp->cmd_matrix);
		if (temp->cmd_path != NULL)
			free(temp->cmd_path);
		if (temp->file != NULL)
			free(temp->file);
		free(temp);
	}
}

int	fill_nodes(t_node **node, t_mini *mini, char *prompt)
{
	int	i;
	int	p;

	p = 0;
	if (!ft_tokenizer(mini, prompt))
		return (0);
	if (!valid_redir(mini))
		return (0);
	if (mini->commands[0] == NULL)
		return (0);
	if (*node != NULL)
	{
		ft_free_tnodes(*node);
		*node = NULL;
	}
	while (p < count_commands_pipes(mini))
	{
		fill_redir(node, mini, p);
		fill_cmd(node, mini, p);
		p++;
	}
	exec(*node, mini);
	signal_handler();
	return (1);
}

int	is_executable(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == 0)
	{
		if (S_ISREG(statbuf.st_mode))
		{
			if (statbuf.st_mode & S_IXUSR || statbuf.st_mode & S_IXGRP
				|| statbuf.st_mode & S_IXOTH)
				return (1);
		}
	}
	return (0);
}
