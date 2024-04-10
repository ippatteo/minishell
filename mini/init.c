/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 23:29:19 by luca              #+#    #+#             */
/*   Updated: 2024/04/10 10:02:25 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	init(t_mini *mini, t_node *node)
{
	node = NULL;
	mini->tmp = NULL;
	mini->commands = NULL;
	mini->tkn = NULL;
	mini->fdin = 0;
	mini->fdout = 1;
	mini->open_quot = 0;
	mini->open_d_quot = 0;
	mini->temp_in = 0;
	mini->temp_out = 0;
	mini->redir_flg_input = 0;
	mini->redir_flg_output = 0;
	mini->sub = NULL;
	signal_handler();
}
