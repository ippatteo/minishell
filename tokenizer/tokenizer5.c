/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/04/02 22:05:57 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../mini.h"

//filla e controlla se c'è il file, se c'è ben altrimenti sull'errore mette 2,
//l'unico morivo per cui mette 2 qua è unexpected token
void fill_redir0(t_node *new, t_mini *mini, int i, int p)
{
	set_values_as_null(new);
	new->this_tkn = mini->tkn[i];
	if (mini->tkn[i + 1] && mini->tkn[i + 1] != PIPE)
		mini->tkn[i + 1] = 1;
	else
	{
		new->error = 2;//unexpected token
		return ;
	}
	new->right_tkn = mini->tkn[i + 1];
	new->n_pipe = p;
	new->file = ft_strdup(mini->commands[i+1]);
}

//mette le redirection sempre
void fill_redir(t_node **node, t_mini *mini, int p)
{
	int i;
	int z;
	t_node *new;

	i = go_int(mini, p);
	z = 0;

	while (mini->tkn[i] && mini->tkn[i] != PIPE)
	{
		if	(mini->tkn[i] <= HERE_DOC && mini->tkn[i] >= REDIR_MIN)
		{
			new = (t_node *)ft_calloc(sizeof(t_node), 1);
			fill_redir0(new, mini, i, p);
			ft_lstadd_back(node, new);
		}
		i++;
	}
}


//porcodeddio la funzione finale

void ft_free_tnodes(t_node *node)
{
	t_node* temp;
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



int fill_nodes(t_node **node, t_mini *mini)
{
	int i;
	int p;

	p = 0;
	if (mini->commands[0] == NULL)
		return (0);
	if (!ft_tokenizer(mini))
		return(0);
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
	ft_close_all(mini);
	return(1);
}
