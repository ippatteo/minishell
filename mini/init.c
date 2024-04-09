/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 23:29:19 by luca              #+#    #+#             */
/*   Updated: 2024/04/09 12:27:53 by mcamilli         ###   ########.fr       */
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
	mini->temp_in = dup(0);
	mini->temp_out = dup(1);
	mini->tknflag = 0;
	mini->pipeline = 0;
	mini->sub = NULL;
	signal_handler();
}
