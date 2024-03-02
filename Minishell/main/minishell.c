/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:42:15 by lpicciri          #+#    #+#             */
/*   Updated: 2024/03/02 15:40:01 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	main(int argc, char ** argv, char **env)
{
	char *cmd;
	t_mini mini;

	(void)argv;
	(void)argc;
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
