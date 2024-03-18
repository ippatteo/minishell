/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:42:15 by lpicciri          #+#    #+#             */
/*   Updated: 2024/03/18 20:49:08 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"


int g_exit;

int	main(int argc, char ** argv, char **env)
{
	char *cmd;
	t_mini mini;
	t_node *node;

	(void)argv;
	(void)argc;
	node = NULL;
	cmd = NULL;
	mini.tmp = NULL;
	mini.commands = NULL;
	mini.tkn = NULL;
	mini.tknflag = 0;
	g_exit = 0;
	copy_env(&mini, env);
	while(1)
	{
		cmd = readline("minishell$ ");
		if (cmd == NULL)
			return(0);
		lexer(&mini, cmd);
		//ft_tokenizer(&mini);
		fill_nodes(&node, &mini);
		//exec(&node, &mini);
		add_history(cmd);
		printf("exit code = %d\n", g_exit);
	}
	return(0);
}
