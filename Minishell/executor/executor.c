/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:24:37 by luca              #+#    #+#             */
/*   Updated: 2024/03/07 23:10:37 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	exec(t_node *node, t_mini *mini)
{
	node->cmd_path = ft_strdup("echo");
	node->cmd_matrix = malloc(sizeof(char *) * 4);
	node->cmd_matrix[0] = "echo";
	node->cmd_matrix[1] = "ciao";
	node->cmd_matrix[2] = "ciao";
	node->cmd_matrix[3] = NULL;

	//ft_cd(node, mini);
	//ft_echo(node, mini);
	//ft_pwd(node, mini);
	ft_env(node, mini);
	return ;
}
