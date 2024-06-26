/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:03:41 by luca              #+#    #+#             */
/*   Updated: 2024/04/11 14:55:55 by lpicciri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_is_command(t_mini *mini, char *cmd)
{
	char	*path;
	char	**folders;
	char	*tmp;
	int		i;

	i = 0;
	if (!access(cmd, X_OK) && is_executable(cmd))
		return (20);
	if (ft_getenv(mini->en, "PATH") == NULL)
		return (0);
	folders = ft_split(ft_getenv(mini->en, "PATH"), ':');
	while (folders[i])
	{
		tmp = ft_strdup_slash(folders[i]);
		free(folders[i]);
		folders[i] = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access (folders[i++], X_OK) && is_executable(folders[i - 1]))
		{
			free_matrix(folders);
			return (20);
		}
	}
	free_matrix(folders);
	return (0);
}

int	assign_number_of_tkn(t_mini *mini, char *cmd)
{
	if (ft_is_pipe_redir_hd(cmd))
		return (ft_is_pipe_redir_hd(cmd));
	else
		return (111);
}

char	*ft_command_path(t_mini *mini, char *cmd)
{
	char	*path;
	char	**folders;
	char	*tmp;
	int		i;

	i = 0;
	if (!access (cmd, X_OK) && is_executable(cmd))
		return (ft_strdup(cmd));
	folders = ft_split(ft_getenv(mini->en, "PATH"), ':');
	while (folders[i])
	{
		tmp = ft_strdup_slash(folders[i]);
		free(folders[i]);
		folders[i] = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(folders[i], X_OK) && is_executable(folders[i]))
		{
			tmp = ft_strdup(folders[i]);
			free_matrix(folders);
			return (tmp);
		}
		i++;
	}
	free_matrix(folders);
	return (NULL);
}

int	ft_tokenizer(t_mini *mini, char *prompt)
{
	int	i;

	i = 0;
	if (!lexer(mini, prompt))
		return (0);
	if (mini->tknflag == 1)
		free(mini->tkn);
	mini->tkn = ft_calloc(count_matrix(mini->commands) + 1, sizeof(char));
	while (mini->commands[i])
	{
		mini->tkn[i] = assign_number_of_tkn(mini, mini->commands[i]);
		i++;
	}
	mini->tkn[i] = '\0';
	mini->tknflag = 1;
	if (!check_pipe_errors(mini))
		return (0);
	i = 0;
	return (1);
}
