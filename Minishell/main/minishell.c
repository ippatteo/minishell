/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:42:15 by lpicciri          #+#    #+#             */
/*   Updated: 2024/03/06 17:11:48 by mcamilli         ###   ########.fr       */
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
	mini.tkn = NULL;
	mini.tknflag = 0;
	copy_env(&mini, env);
	while(1)
	{
		cmd = readline("minishell$ ");
		if (cmd == NULL)
			return(0);
		lexer(&mini, cmd);
		ft_tokenizer(&mini);
		add_history(cmd);
	}
	return(0);
}
