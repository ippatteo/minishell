/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:42:15 by lpicciri          #+#    #+#             */
/*   Updated: 2024/03/07 10:18:11 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"
/*
legenda: 
n = 100 (è una parola, quindi magari un argomento)
n = 111 (è un file presente nella cartella di lavoro)
n = 11 (è la builtin echo)
n = 12 (è la builtin cd)
n = 13 (è la builtin pwd)
n = 14 (è la builtin export)
n = 15 (è la builtin unset)
n = 16 (è la builtin env)
n = 17 (è la builtin exit)
n = 20 (è un command trovato che esiste e si trova in $PATH) 
n = 1 (è una pipe "|")
n = 2 (è una redirecion ">")
n = 3 (è una redirecion "<")
n = 4 (è una redirecion ">>")
n = 77 (è un here document "<<")

*/



int ft_is_builtin(char *cmd)
{
	if (!ft_strncmp("echo", cmd, 4))
		return (11);
	else if(!ft_strncmp("cd", cmd, 2))
		return (12);
	else if(!ft_strncmp("pwd", cmd, 3))
		return (13);
	else if (!ft_strncmp("export", cmd, 7))
		return (14);
	else if (!ft_strncmp("unset", cmd, 6))
		return (15);
	else if (!ft_strncmp("env", cmd, 3))
		return (16);
	else if (!ft_strncmp("exit", cmd, 4))
		return (17);
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
	str_allocated = malloc(len + 2);
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
char *ft_is_command(char *cmd)
{
	char	*path;
	char	**folders;
	char	*tmp;
	int		i;
	
	i = 0;
	if(access(cmd , X_OK) == 0)
		return (cmd);
	folders = ft_split(getenv("PATH"), ':');
	while (folders[i])
	{
		tmp = ft_strdup_slash(folders[i]);
		free(folders[i]);
		folders[i] = ft_strjoin(tmp, cmd);
		free(tmp);
		if(access(folders[i], X_OK) == 0)
		{	
			tmp = ft_strdup(folders[i]);
			free_matrix(folders);
			return(tmp);
		}
		i++;
	}
	free_matrix(folders);
	return (NULL);
}

int ft_is_pipe_redir_hd(char *cmd)
{
	if (*cmd == '|')
		return (1);
	else if (*cmd == '>' && *(cmd+1) == '>')
		return (4);
	else if (*cmd == '<' && *(cmd+1) == '<')
		return (77);
	else if(*cmd == '>')
		return (2);
	else if(*cmd == '<')
		return (3);
	else
		return (0);
}
char *ft_is_file(char *cmd)
{
	char	*path;
	char	*folder;;
	int		i;
	char *tmp;
	
	if(access(cmd , F_OK) == 0)
		return (cmd);
	tmp = ft_strdup_slash(folder);
	i = 0;
	folder = ft_strdup(getenv("PWD"));
	tmp = ft_strdup_slash(folder);
	free(folder);
	folder = ft_strjoin(tmp, cmd);
	if(access(folder, F_OK) == 0)
		return(folder);
	free(folder);
	return (NULL);
}


int assign_number_of_tkn(t_mini *mini, char *cmd)
{
	if (ft_is_builtin(cmd))
		return (ft_is_builtin(cmd));
	else if (ft_is_pipe_redir_hd(cmd))
		return(ft_is_pipe_redir_hd(cmd));
	else if (ft_is_file(cmd))
	{
		printf("%s\n",ft_is_file(cmd));
		return(111);
	}
	else if (ft_is_command(cmd))
		return (20);
	else
		return (100);	
}

void ft_tokenizer(t_mini *mini)
{
	int i;

	i= 0;
	if (mini->tknflag == 1)
		free(mini->tkn);
	mini->tkn = ft_calloc(mini->lines, sizeof(int));
	while (mini->commands[i])
	{
		mini->tkn[i] = assign_number_of_tkn(mini, mini->commands[i]);
		printf("tkn = %d\n", mini->tkn[i]);
		i++;
	}
	mini->tknflag = 1;
}


