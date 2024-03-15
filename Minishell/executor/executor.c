/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:24:37 by luca              #+#    #+#             */
/*   Updated: 2024/03/13 17:38:24 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	exec(t_node *node, t_mini *mini)
{
	node->cmd_path = "/bin/ls";
	node->cmd_matrix = malloc(sizeof(char *) * 2);
	node->cmd_matrix[0] = "/bin/ls";
	node->cmd_matrix[1] = NULL;
	node->type = PIPE;
	node->left_tkn = 0;
	node->right_tkn = PIPE;
	node->next = malloc(sizeof(t_node));
	node->next->type = PIPE;
	node->next->cmd_path = "/usr/bin/cat";
	node->next->cmd_matrix = malloc(sizeof(char *) * 2);
	node->next->cmd_matrix[0] = "/usr/bin/cat";
	node->next->cmd_matrix[1] = NULL;
	node->next->left_tkn = PIPE;
	node->next->right_tkn = 0;
	node->next->next = malloc(sizeof(t_node));
	node->next->next->type = PIPE;
	node->next->next->cmd_path = "/bin/wc";
	node->next->next->cmd_matrix = malloc(sizeof(char *) * 2);
	node->next->next->cmd_matrix[0] = "/bin/wc";
	node->next->next->cmd_matrix[1] = NULL;
	node->next->next->left_tkn = PIPE;
	node->next->next->right_tkn = END_PIPE;
	pipex(node);
	//ft_cd(node, mini);
	//ft_echo(node, mini);
	//ft_pwd(node, mini);
	//ft_env(node, mini);
	return ;
}
