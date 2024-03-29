/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:42:15 by lpicciri          #+#    #+#             */
/*   Updated: 2024/03/21 19:26:25 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void ft_exit_all(t_node *node, t_mini *mini)
{
	//free_env(mini);
	free_matrix(mini->en);
		//mini->en = NULL;
		write(1,"1wert\n", 6);
	if (mini->tkn == NULL)	
		free(mini->tkn);
	write(1,"2wert\n", 6);
	if (mini->commands != NULL)
	{
		free_matrix(mini->commands);
	}
	write(1,"3wert\n", 6);
	if (node != NULL)
		ft_free_tnodes(node);
	write(1,"4wert\n", 6);
}
void	sig_handle(int signum)
{
	if(signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if(signum == SIGTERM)
	{
		exit(1);
	}

}

void	signal_handler()
{
	signal(SIGINT,  sig_handle);
	signal(SIGTERM, sig_handle);
	signal(SIGQUIT, SIG_IGN);
}

int g_exit;
void free_env(t_mini *mini) {
    int i = 0;

    if (mini->en != NULL) {
        while (mini->en[i] != NULL) {
            free(mini->en[i]);  // Libera ogni stringa
            i++;
        }
        free(mini->en);  // Poi libera l'array di puntatori
        mini->en = NULL;  // Imposta il puntatore a NULL per sicurezza
    }
}



int	main(int argc, char ** argv, char **env)
{
	char *cmd;
	t_mini mini;
	t_node *node;
	static int i;

	(void)argv;
	(void)argc;
	node = NULL;
	cmd = NULL;
	mini.tmp = NULL;
	mini.commands = NULL;
	mini.tkn = NULL;
	mini.tknflag = 0;
	g_exit = 0;
	char **matrix;

	matrix = malloc(sizeof(char *) * 4);
	matrix[0] = "export";
	matrix[1] = "pipo=ao";
	matrix[2] = "PIPPOBAUDO=aooooooooo";
	matrix[3] = NULL;
	
	copy_env(&mini, env);
	ft_printmap1(mini.en);
	while(1)
	{
		signal_handler();
		cmd = readline("minishell$ ");
		if (cmd == NULL)
		{
			ft_exit_all(node, &mini);
			return(0);
		}
		if (*cmd != 0)
		{
			lexer(&mini, cmd);
			//ft_tokenizer(&mini);
			fill_nodes(&node, &mini);
			exec(node, &mini);
			add_history(cmd);
			printf("exit code = %d\n", g_exit);
		}
	}
	printf("qwertyuio\n\n");
	ft_exit_all(node, &mini);
	return(0);
}
