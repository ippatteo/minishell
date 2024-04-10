/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:04:27 by luca              #+#    #+#             */
/*   Updated: 2024/04/03 00:04:39 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	set_values_as_null(t_node *node)
{
	node->cmd_path = NULL;
	node->cmd_matrix = NULL;
	node->left_tkn = 0;
	node->right_tkn = 0;
	node->this_tkn = 0;
	node->file = NULL;
	node->next = NULL;
	node->error = 0;
	node->n_pipe = -1;
}

int	set_fill_error(t_node *new, t_mini *mini, int p, int i)
{
	int	t;

	t = 1;
	new->n_pipe = p;
	new->cmd_matrix = ft_calloc(sizeof(char *),
			fill_cmd_count_args(mini, p) + 2);
	t = 1;
	new->cmd_matrix[0] = find_cmd_or_b_in(mini, i);
	new->cmd_path = find_cmd_or_b_in(mini, i);
	while (mini->tkn[i] && mini->tkn[i] != PIPE)
	{
		if (mini->tkn[i] == ARGS)
			new->cmd_matrix[t++] = ft_strdup(mini->commands[i]);
		i++;
	}
	new->cmd_matrix[t] = NULL;
	return (0);
}

int	there_is_pipe(t_mini *mini, int i)
{
	while (mini->tkn[i])
	{
		if (mini->tkn[i] == PIPE)
			return (PIPE);
		i++;
	}
	return (END_PIPE);
}

int	cmd_error(t_mini *mini, t_node *new, int i)
{
	if (!(ft_is_builtin(mini->commands[i])
			|| ft_is_command(mini, mini->commands[i])))
	{
		new->error = 127;
		new->cmd_path = ft_strdup(mini->commands[i]);
		new->this_tkn = ARGS;
		return (0);
	}
	else if (ft_is_builtin(mini->commands[i]))
		mini->tkn[i] = ft_is_builtin(mini->commands[i]);
	else if (ft_is_command(mini, mini->commands[i]))
		mini->tkn[i] = ft_is_command(mini, mini->commands[i]);
	return (1);
}

void	fill_cmd(t_node **node, t_mini *mini, int p)
{
	int		i;
	int		t;
	t_node	*new;

	if (find_pos_cmd(mini, p) == -1)
		return ;
	i = find_pos_cmd(mini, p);
	new = (t_node *)ft_calloc(sizeof(t_node), 1);
	set_values_as_null(new);
	new->right_tkn = there_is_pipe(mini, i);
	if (p)
		new->left_tkn = PIPE;
	else
		new->left_tkn = START_P;
	while (mini->tkn[i] != ARGS)
		i++;
	if (!cmd_error(mini, new, i))
	{
		ft_lstadd_back(node, new);
		return ;
	}
	new->this_tkn = mini->tkn[i];
	set_fill_error(new, mini, p, i);
	ft_lstadd_back(node, new);
}
