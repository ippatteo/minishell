/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:42:15 by lpicciri          #+#    #+#             */
/*   Updated: 2024/02/23 13:19:05 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	main(int argc, char ** argv, char **env)
{
	char *cmd;
	t_mini mini;

	(void)argc;
	(void)argv;
	cmd = NULL;
	mini.tmp = NULL;
	mini.commands = NULL;
	copy_env(&mini, env);
	while(1)
	{
		cmd = readline("minishell$ ");
		if (cmd == NULL)
			return(0);
		lexer(&mini, cmd);
		add_history(cmd);
	}
	return(0);
}
