/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:24:37 by luca              #+#    #+#             */
/*   Updated: 2024/04/04 03:30:56 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	here_doc(t_node *node, t_mini *mini)
{
	char	*str;
	char	**cmd;
	int		fd[2];
	int		i;

	i = 0;
	if (pipe(fd) == -1)
		ft_putendl_fd(strerror(errno), 2);
	while (1)
	{
		signal_heredoc();
		str = readline("> ");
		if (str == NULL)
			return ;
		if (ft_strcmp(str, node->file) == 0)
			break ;
		write(fd[1], str, ft_strlen(str));
		free(str);
		write(fd[1], "\n", 1);
		i++;
	}
	mini->fdin = fd[0];
	close(fd[1]);
	mini->redir_flag = 1;
}

void	redir_mag(t_node *node, t_mini *mini)
{
	int	fd;

	fd = open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	mini->fdout = fd;
	mini->redir_flag = 1;
}

void	redir_magmag(t_node *node, t_mini *mini)
{
	int	fd;

	fd = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	mini->fdout = fd;
	mini->redir_flag = 1;
}

int	redir_min(t_node *node, t_mini *mini)
{
	char	*path;
	int		fd;

	fd = open(node->file, O_RDONLY);
	if (fd == -1)
	{
		g_exit = 2;
		ft_putendl_fd("no such file or directory", 2);
		return (0);
	}
	mini->fdin = fd;
	mini->redir_flag = 1;
	return (1);
}

int	redirection_init(t_node *node, t_mini *mini)
{
	if (node->this_tkn == REDIR_MAG)
		redir_mag(node, mini);
	if (node->this_tkn == REDIR_MAGMAG)
		redir_magmag(node, mini);
	if (node->this_tkn == REDIR_MIN)
	{
		if (!redir_min(node, mini))
			return (0);
	}
	if (node->this_tkn == HERE_DOC)
		here_doc(node, mini);
	return (1);
}
