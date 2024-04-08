/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:24:37 by luca              #+#    #+#             */
/*   Updated: 2024/04/08 18:18:01 by lpicciri         ###   ########.fr       */
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
