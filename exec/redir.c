/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:24:37 by luca              #+#    #+#             */
/*   Updated: 2024/04/10 11:48:14 by luca             ###   ########.fr       */
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
	mini->redir_flg_input = 1;
	close(fd[1]);
}

void	redir_mag(t_node *node, t_mini *mini)
{
	int	fdout;

	fdout = open(node->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (mini->fdout < 0)
	{
		g_exit = 1;
		perror("file error");
	}
	if(dup2(fdout, STDOUT_FILENO) == -1)
		perror("dup mag \n");
	close(fdout);	
	mini->redir_flg_output = 1;
}

void	redir_magmag(t_node *node, t_mini *mini)
{
	int	fdout;

	fdout = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (mini->fdout < 0)
	{
		g_exit = 1;
		perror("file error");
	}
	if(dup2(fdout, STDOUT_FILENO) == -1)
		perror("dup mag mag\n");
	close(fdout);
	mini->redir_flg_output = 1;
}

int	redir_min(t_node *node, t_mini *mini)
{
	int	fdin;

	fdin = open(node->file, O_RDONLY);
	if (mini->fdin < 0)
	{
		g_exit = 1;
		ft_putendl_fd("no such file\n", 2);
		return (-1);
	}
	if(dup2(fdin, STDIN_FILENO) == -1)
		perror("dup min\n");
	close(fdin);
	mini->redir_flg_input = 1;
	return (0);
}

int	redirection_init(t_node *node, t_mini *mini)
{
	if (node->this_tkn == REDIR_MAG)
		redir_mag(node, mini);
	if (node->this_tkn == REDIR_MAGMAG)
		redir_magmag(node, mini);
	if (node->this_tkn == REDIR_MIN)
	{
		if (redir_min(node, mini) == -1)
			return (-1);
	}
	if (node->this_tkn == HERE_DOC)
		here_doc(node, mini);
	return (0);
}
