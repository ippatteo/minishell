/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:24:37 by luca              #+#    #+#             */
/*   Updated: 2024/04/02 17:36:46 by mcamilli         ###   ########.fr       */
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
		if (ft_strcmp(str, node->file) == 0)
			break ;
		write(fd[1], str, ft_strlen(str));
		free(str);
		write(fd[1], "\n", 1);
		i++;
	}
	mini->curr_input = fd[0];
	close(fd[1]);
}

void	redir_mag(t_node *node, t_mini *mini)
{
	int	fd;

	if (mini->curr_output != 1)
		close(mini->curr_output);
	fd = open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	mini->curr_output = fd;
}

void	redir_magmag(t_node *node, t_mini *mini)
{
	int	fd;

	if (mini->curr_output != 1)
		close(mini->curr_output);
	fd = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	mini->curr_output = fd;
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
	mini->curr_input = fd;
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
