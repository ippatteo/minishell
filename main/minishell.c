/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:42:15 by lpicciri          #+#    #+#             */
/*   Updated: 2024/03/21 14:22:56 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

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
		exit(1);

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

void ft_exit_all(t_node *node, t_mini *mini)
{
	//free_env(mini);
	free_matrix(mini->en);
	free (mini->tkn);
	free_matrix(mini->commands);
	ft_free_tnodes(node);
}

int	main(int argc, char ** argv, char **env)
{
	char *cmd;
	t_mini mini;
	t_node *node;
	t_pipes	*pipes;
	static int i;

	(void)argv;
	(void)argc;
	node = NULL;
	cmd = NULL;
	mini.tmp = NULL;
	mini.commands = NULL;
	mini.tkn = NULL;
	mini.fd_stdin = dup(STDIN_FILENO);
	mini.fd_stdout = dup(STDOUT_FILENO);
	mini.curr_input = 0;
	mini.curr_output = 1;
	mini.tknflag = 0;
	signal_handler();
	g_exit = 0;
	copy_env(&mini, env);
	while(1)
	{
		cmd = readline("minishell$ ");
		if (cmd == NULL)
			return(0);
		lexer(&mini, cmd);
		fill_nodes(&node, &mini);
		exec(node, &mini);
		add_history(cmd);
		printf("exit code = %d\n", g_exit);
		i++;
		if (i == 3)
		{
			ft_exit_all(node, &mini);
			return (0);
		}
	}
	return(0);
}
