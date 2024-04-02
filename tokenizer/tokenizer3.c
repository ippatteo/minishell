/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 20:08:48 by lpicciri          #+#    #+#             */
/*   Updated: 2024/04/02 20:08:51 by lpicciri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	go_int(t_mini *mini, int p)
{
	int	i;
	int	z;

	i = 0;
	z = 0;
	while (z < p && mini->commands[i])
	{
		if (mini->tkn[i] == PIPE)
			z++;
		i++;
	}
	return (i);
}

char	*find_cmd_or_b_in(t_mini *mini, int pos)
{
	if (mini->tkn[pos] >= 11 && mini->tkn[pos] <= 17)
		return (ft_strdup(mini->commands[pos]));
	else if (mini->tkn[pos] == 20)
		return (ft_command_path(mini, mini->commands[pos]));
	else
		return (NULL);
}

int	count_commands_pipes(t_mini *mini)
{
	int	i;
	int	p;

	i = 0;
	p = 1;
	while (mini->commands[i])
	{
		if (mini->tkn[i] == PIPE)
			p++;
		i++;
	}
	return (p);
}

// trova la posizione del comando o built in
int	find_pos_cmd(t_mini *mini, int p)
{
	int	i;
	int	z;

	i = go_int(mini, p);
	z = 0;
	while (mini->tkn[i] && mini->tkn[i] != PIPE)
	{
		if (mini->tkn[i] >= BUILTIN
			&& mini->tkn[i] <= COMMAND || mini->tkn[i] == ARGS)
			return (i);
		i++;
	}
	return (-1);
}

int	fill_cmd_count_args(t_mini *mini, int p)
{
	int	i;
	int	t;

	i = find_pos_cmd(mini, p);
	t = 0;
	while (mini->tkn[i] && mini->tkn[i] != PIPE)
	{
		if (mini->tkn[i] == ARGS)
			t++;
		i++;
	}
	return (t);
}
