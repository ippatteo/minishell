/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 23:29:19 by luca              #+#    #+#             */
/*   Updated: 2024/04/08 16:20:05 by luca             ###   ########.fr       */
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
	mini->temp_in = dup(0);
	mini->temp_out = dup(1);
	mini->tknflag = 0;
	mini->pipeline_flg = 0;
	mini->sub = NULL;
	signal_handler();
}
