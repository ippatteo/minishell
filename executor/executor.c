/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:24:37 by luca              #+#    #+#             */
/*   Updated: 2024/03/20 21:10:41 by luca             ###   ########.fr       */
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
		matrix[i] = readline("> ");
		printf("ciao");
		if (ft_strcmp(matrix[i], node->file) == 0)
		{
			matrix[i] = NULL;
			break ;
		}
		i++;
	}
	if(dup2(fd[0], STDOUT_FILENO) == -1)
		ft_putendl_fd(strerror(errno), 2);
	ft_printmap0(matrix);
	if(dup2(fd[1], STDIN_FILENO) == -1)
		ft_putendl_fd(strerror(errno), 2);
	close(fd[0]);
	close(fd[1]);
}

void	redir_mag(t_node *node, t_mini *mini)
{
	int	fd;

	fd = open(node->file, O_CREAT | O_RDONLY | O_WRONLY);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_magmag(t_node *node, t_mini *mini)
{
	int	fd;

	fd = open(node->file, O_CREAT | O_APPEND | O_RDONLY | O_WRONLY);
	dup2(fd, STDOUT_FILENO);
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
	fd = open(node->file, O_RDONLY);
	dup2(fd, STDIN_FILENO);
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

void	exec(t_node *node, t_mini *mini)
{
	while(node)
	{
		if (node->this_tkn < 10 && node->this_tkn >2)
			redirection_init(node, mini);
		node = node->next;
	}
	dup2(mini->fd_stdout, STDOUT_FILENO);
	dup2(mini->fd_stdin, STDIN_FILENO);
	return ;
}
