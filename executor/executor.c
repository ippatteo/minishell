/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:24:37 by luca              #+#    #+#             */
/*   Updated: 2024/03/21 18:27:35 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	here_doc(t_node *node, t_mini *mini)
{
	char **matrix;
	char **cmd;
	int	fd[2];
	int	i;

	i = 0;
	if(pipe(fd) == -1)
		ft_putendl_fd(strerror(errno), 2);
	while(1)
	{
		ft_putendl_fd("###ciao", 2);
		matrix[i] = readline("> ");
		if (ft_strcmp(matrix[i], node->file) == 0)
		{
			matrix[i] = NULL;
			break ;
		}
		i++;
	}
	if(dup2(fd[0], mini->curr_input) == -1)
		ft_putendl_fd(strerror(errno), 2);
	if(dup2(fd[1], mini->curr_output) == -1)
		ft_putendl_fd(strerror(errno), 2);
	close(fd[0]);
	close(fd[1]);
}

void	redir_mag(t_node *node, t_mini *mini)
{
	int	fd;

	fd = open(node->file , O_CREAT | O_WRONLY | O_RDONLY);
	dup2(fd, mini->curr_output);
	mini->curr_output = fd;
}

void	redir_magmag(t_node *node, t_mini *mini)
{
	int	fd;

	fd = open(node->file, O_CREAT | O_APPEND, 0777);
	dup2(fd, mini->curr_output);
	mini->curr_output = fd;
	close(fd);
}

void	redir_min(t_node *node, t_mini *mini)
{
	char *path;
	int	fd;

	path = getcwd(NULL, 0);
	path = ft_strjoin(path, "/");
	path = ft_strjoin(path, node->file);
	if(access(path, R_OK) == -1)
	{
		g_exit = 2;
		ft_putendl_fd("no such file or directory", 2);
	}
	fd = open(node->file, O_RDWR);
	dup2(fd, mini->curr_input);
	mini->curr_input = fd;
	close(fd);
}


void	redirection_init(t_node *node, t_mini *mini)
{
	if (node->this_tkn == REDIR_MAG)
		redir_mag(node, mini);
	if (node->this_tkn == REDIR_MAGMAG)
		redir_magmag(node, mini);
	if (node->this_tkn == REDIR_MIN)
		redir_min(node, mini);
	if (node->this_tkn == HERE_DOC)
		here_doc(node, mini);
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
	waitpid(-1, NULL, 0);
}

void	exec_single(t_node *node, t_mini *mini)
{
	if (node->this_tkn > 10 && node->this_tkn < 20)
		exec_builtin(node, mini);
	if (node->this_tkn == 20)
		exec_command(node, mini);
}

void	exec(t_node *node, t_mini *mini)
{
	while(node)
	{
		if (node->this_tkn < 10 && node->this_tkn > 2)
			redirection_init(node, mini);
		if (node->next == NULL)
			exec_single(node, mini);
		node = node->next;
	}
	dup2(mini->fd_stdout, 1);
	dup2(mini->fd_stdin, 0);
	return ;
}
