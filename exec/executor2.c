/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:07:30 by mcamilli          #+#    #+#             */
/*   Updated: 2024/04/02 16:47:19 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int err_quote(t_mini *mini)
{
	int i;

	i = 0;
	while (mini->commands[i])
	{
		if (mini->commands[i][0] == D_QUOT || mini->commands[i][0] == QUOT)
		{
			if (mini->commands[i][0] == D_QUOT && (ft_strlen(mini->commands[i])-1))
			{
				if(mini->commands[i][ft_strlen(mini->commands[i])-1] != D_QUOT)
					return(0);
			}
			else if(mini->commands[i][0] == QUOT && (ft_strlen(mini->commands[i])-1))
			{
				if (mini->commands[i][ft_strlen(mini->commands[i])-1] != QUOT)
					return(0);
			}
		}
		i++;
	}
	return (1);
}

int is_there_redir(t_mini *mini)
{
	int i;
	
	i = 0;
	while (mini->tkn[i])
	{
		if (mini->tkn[i] == 1)
			return (1);
		i++;
	}
	return (0);
}
void	exec_builtin(t_node *node, t_mini *mini)
{
	if (node->this_tkn == CD)
		ft_cd(node, mini);
	if (node->this_tkn == ECHO)
		ft_echo(node, mini);
	if (node->this_tkn == PWD)
		ft_pwd(node, mini);
	if (node->this_tkn == EXPORT)
		ft_export(node, mini);
	if (node->this_tkn == UNSET)
		ft_unset(mini, node->cmd_matrix);
	if (node->this_tkn == ENV)
		ft_env(node, mini);
	if (node->this_tkn == EXIT)
		ft_exit(node, mini);
}

void	exec_command(t_node *node,t_mini *mini)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		execve(node->cmd_path, node->cmd_matrix, NULL);
	while(waitpid(pid, NULL, 0)>0);
}

void	exec_single(t_node *node, t_mini *mini)
{
	
	int original_stdin;
	int original_stdout;
	
	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	if (mini->curr_input != STDIN_FILENO)
		dup2(mini->curr_input, STDIN_FILENO);
	if (mini->curr_output != STDOUT_FILENO)
		dup2(mini->curr_output, STDOUT_FILENO);
	if (node->this_tkn > 10 && node->this_tkn < 20)
		exec_builtin(node, mini);
	if (node->this_tkn == 20)
		exec_command(node, mini);
	if (dup2(original_stdin, STDIN_FILENO) == -1)
		perror("Errore nel ripristinare stdin");
	if (dup2(original_stdout, STDOUT_FILENO) == -1)
		perror("Errore nel ripristinare stdout");
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}

void ft_close_all(t_mini *mini)
{
	if (mini->curr_input != STDIN_FILENO)
	{
		close(mini->curr_input);
		mini->curr_input = STDIN_FILENO;
	}
	if (mini->curr_output != STDOUT_FILENO)
	{
		close(mini->curr_output);
		mini->curr_output = STDOUT_FILENO;
	}
}