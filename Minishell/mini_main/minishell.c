/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:42:15 by lpicciri          #+#    #+#             */
/*   Updated: 2024/02/21 18:43:43 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	main()
{
	char *cmd;
	t_mini mini;

	cmd = NULL;
	mini.commands = NULL;
	while(1)
	{
		cmd = readline("minishell$ ");
		if (cmd == NULL)
			return(-1);
		lexer(&mini, cmd);
		add_history(cmd);
	}
	return(0);
}
