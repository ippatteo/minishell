/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:42:15 by lpicciri          #+#    #+#             */
/*   Updated: 2024/02/19 10:00:42 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/minishell.h"

int	main()
{
	char *cmd;

	cmd = NULL;
	while(1)
	{
		cmd = readline("minishell$ ");
		if (cmd == NULL)
			return(-1);
		//printf("\n%d\n", (int)count_mem(cmd));
		//	lexer(cmd);
		//add_history(cmd);
	}
	return(0);
}
