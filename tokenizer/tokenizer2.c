/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/04/02 16:54:12 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../mini.h"


int is_executable(const char *path) 
{
    struct stat st;

    if (stat(path, &st) == 0) {
        // Controlla se il file è un file regolare e se è eseguibile.
        if (S_ISREG(st.st_mode) && (st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))) {
            return 1; // Il file è eseguibile.
        }
    }

    return 0; // Il file non è eseguibile o non esiste.
}

int ft_is_command(t_mini *mini, char *cmd)
{
	char	*path;
	char	**folders;
	char	*tmp;
	int		i;

	i = 0;
	if(access(cmd , X_OK) == 0)
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
		if(access(folders[i], X_OK) == 0 && is_executable(folders[i]))
		{
			free_matrix(folders);
			return(20);
		}
		i++;
	}
	free_matrix(folders);
	return (0);
}

int assign_number_of_tkn(t_mini *mini, char *cmd)
{
	//if (ft_is_builtin(cmd) != 0)
	//	return (ft_is_builtin(cmd));
	if (ft_is_pipe_redir_hd(cmd))
		return(ft_is_pipe_redir_hd(cmd));
	//else if (ft_is_command(mini, cmd))
		//return (20);
	else
		return (111);
}
char *ft_command_path(t_mini *mini, char *cmd)
{
	char	*path;
	char	**folders;
	char	*tmp;
	int		i;

	i = 0;
	if(access(cmd , X_OK) == 0)
		return (cmd);
	folders = ft_split(ft_getenv(mini->en, "PATH"), ':');
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

int ft_tokenizer(t_mini *mini)
{
	int i;

	i= 0;
	if (mini->tknflag == 1)
		free(mini->tkn);
	mini->tkn = ft_calloc(count_matrix(mini->commands) + 1, sizeof(char));
	while (mini->commands[i])
	{
		mini->tkn[i] = assign_number_of_tkn(mini, mini->commands[i]);
		i++;
	}
	mini->tkn[i] = '\0';
	mini->tknflag = 1;//potrebbe esse provvisorio, ma ora mi permette di freeare
	if (!err_quote(mini))
	{
		g_exit = 127;
		ft_putendl_fd("d_quote col cazzo che lo implemento", 2);
		return (0);
	}
	realloc_quotes(mini);
	if (!check_pipe_errors(mini))
		return (0);
	i = 0;
	return (1);

}
