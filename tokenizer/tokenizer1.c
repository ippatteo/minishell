/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:04:49 by luca              #+#    #+#             */
/*   Updated: 2024/04/03 13:58:26 by lpicciri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	check_pipe_errors(t_mini *mini)
{
	int	i;
	int	flag_found_cmd;

	i = 1;
	flag_found_cmd = 0;
	if (mini->tkn[0] == PIPE)
	{
		g_exit = 2;
		return (0);
	}
	while (mini->tkn[i])
	{
		if (mini->tkn[i] == PIPE)
		{
			if (!mini->tkn[i + 1])
			{
				g_exit = 2;
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	ft_is_builtin(char *cmd)
{
	if (ft_strlen(cmd) == 4 && !ft_strncmp("echo", cmd, 4))
		return (ECHO);
	else if (ft_strlen(cmd) == 2 && !ft_strncmp("cd", cmd, 2))
		return (CD);
	else if (ft_strlen(cmd) == 3 && !ft_strncmp("pwd", cmd, 3))
		return (PWD);
	else if (ft_strlen(cmd) == 6 && !ft_strncmp("export", cmd, 6))
		return (EXPORT);
	else if (ft_strlen(cmd) == 5 && !ft_strncmp("unset", cmd, 5))
		return (UNSET);
	else if (ft_strlen(cmd) == 3 && !ft_strncmp("env", cmd, 3))
		return (ENV);
	else if (ft_strlen(cmd) == 4 && !ft_strncmp("exit", cmd, 4))
		return (EXIT);
	else
		return (0);
}

char	*ft_strdup_slash(const char *str)
{
	char	*str_allocated;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(str);
	str_allocated = ft_calloc(1, len + 2);
	if (!str_allocated)
		return (NULL);
	while (str[i] != '\0')
	{
		str_allocated[i] = str[i];
		i++;
	}
	str_allocated[i++] = '/';
	str_allocated[i] = '\0';
	return (str_allocated);
}

int	ft_is_pipe_redir_hd(char *cmd)
{
	if (*cmd == '|')
		return (PIPE);
	else if (*cmd == '>' && *(cmd +1) == '>')
		return (REDIR_MAGMAG);
	else if (*cmd == '<' && *(cmd +1) == '<')
		return (HERE_DOC);
	else if (*cmd == '>')
		return (REDIR_MAG);
	else if (*cmd == '<')
		return (REDIR_MIN);
	else
		return (0);
}
