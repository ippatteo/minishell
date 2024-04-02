/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/04/02 16:53:07 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../mini.h"

//controlla che le pipe siano non prime e non ultime
int check_pipe_errors(t_mini *mini)
{
	int i;
	int flag_found_cmd;

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


void ft_printnode(t_node *node)
{
	t_node *tmp;
	static int i;

	tmp = node;
	if (!node)
		return;
	i = 0;
	while (tmp != NULL)
	{
		printf("node path = %s\n", tmp->cmd_path);
		printf("node left_tkn = %d\n", tmp->left_tkn);
		printf("node right_tkn = %d\n", tmp->right_tkn);
		printf("node this_tkn = %d\n", tmp->this_tkn);
		printf("node file= %s\n", tmp->file);
		if (node->cmd_matrix)
		{
			write(1, "cmd_matrix =\n", 14);
			ft_printmap0(node->cmd_matrix);
		}
		else
			printf("cmd_matrix = NULL\n");
		printf("\n--------------------\n");
		tmp = tmp->next;
	}
}

int ft_is_builtin(char *cmd)
{
	if (!ft_strncmp("echo", cmd, 4))
		return (ECHO);
	else if(!ft_strncmp("cd", cmd, 2))
		return (CD);
	else if(!ft_strncmp("pwd", cmd, 3))
		return (PWD);
	else if (!ft_strncmp("export", cmd, 7))
		return (EXPORT);
	else if (!ft_strncmp("unset", cmd, 6))
		return (UNSET);
	else if (!ft_strncmp("env", cmd, 3))
		return (ENV);
	else if (!ft_strncmp("exit", cmd, 4))
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

int ft_is_pipe_redir_hd(char *cmd)
{
	if (*cmd == '|')
		return (PIPE);
	else if (*cmd == '>' && *(cmd+1) == '>')
		return (REDIR_MAGMAG);
	else if (*cmd == '<' && *(cmd+1) == '<')
		return (HERE_DOC);
	else if(*cmd == '>')
		return (REDIR_MAG);
	else if(*cmd == '<')
		return (REDIR_MIN);
	else
		return (0);
}
