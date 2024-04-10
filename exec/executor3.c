/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:24:37 by luca              #+#    #+#             */
/*   Updated: 2024/04/09 22:45:24 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	handle(int signum)
{
	if (signum == SIGQUIT)
	{
		write(1, "QUIT (core dump)\n", 17);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

int	isredir(t_node *node)
{
	if (node->this_tkn == REDIR_MAG || node->this_tkn == REDIR_MAGMAG
		|| node->this_tkn == REDIR_MIN || node->this_tkn == HERE_DOC)
		return (0);
	return (1);
}

int	isbuiltin(t_node *node)
{
	if (node->this_tkn == EXIT)
		return (1);
	if (node->this_tkn == ECHO)
		return (1);
	if (node->this_tkn == PWD)
		return (1);
	if (node->this_tkn == CD)
		return (1);
	if (node->this_tkn == ENV)
		return (2);
	if (node->this_tkn == EXPORT)
		return (2);
	if (node->this_tkn == UNSET)
		return (2);
	return (0);
}
