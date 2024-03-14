/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:42:15 by lpicciri          #+#    #+#             */
/*   Updated: 2024/03/14 13:25:00 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"
/*
legenda: 
n = 1 (è una parola, quindi magari un argomento)
n = 11 (è la builtin echo)
n = 12 (è la builtin cd)
n = 13 (è la builtin pwd)
n = 14 (è la builtin export)
n = 15 (è la builtin unset)
n = 16 (è la builtin env)
n = 17 (è la builtin exit)
n = 20 (è un command trovato che esiste e si trova in $PATH) 
n = 2 (è una pipe "|")
n = 7 (è una redirecion ">")
n = 3 (è una redirecion "<")
n = 4 (è una redirecion ">>")
n = 9 (è un here document "<<")

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

int ft_is_command(char *cmd)
{
	char	*path;
	char	**folders;
	char	*tmp;
	int		i;
	
	i = 0;
	if(access(cmd , X_OK) == 0)
		return (1);
	folders = ft_split(getenv("PATH"), ':');
	while (folders[i])
	{
		tmp = ft_strdup_slash(folders[i]);
		free(folders[i]);
		folders[i] = ft_strjoin(tmp, cmd);
		free(tmp);
		if(access(folders[i], X_OK) == 0)
		{	
			free_matrix(folders);
			return(1);
		}
		i++;
	}
	free_matrix(folders);
	return (0);
}

int ft_is_pipe_redir_hd(char *cmd)
{
	if (*cmd == '|')
		return (2);
	else if (*cmd == '>' && *(cmd+1) == '>')
		return (4);
	else if (*cmd == '<' && *(cmd+1) == '<')
		return (9);
	else if(*cmd == '>')
		return (7);
	else if(*cmd == '<')
		return (3);
	else
		return (0);
}


int assign_number_of_tkn(t_mini *mini, char *cmd)
{
	if (ft_is_builtin(cmd) != 0)
		return (ft_is_builtin(cmd));
	else if (ft_is_pipe_redir_hd(cmd))
		return(ft_is_pipe_redir_hd(cmd));
	else if (ft_is_command(cmd))
		return (20);
	else
		return (1);	
}
char *ft_command_path(char *cmd)
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

void ft_tokenizer(t_mini *mini)
{
	int i;
	//t_node node;

	//node = malloc(sizeof(t_node));
	i= 0;
	if (mini->tknflag == 1)
		free(mini->tkn);
	mini->tkn = ft_calloc(mini->lines, sizeof(char) +1);
	while (mini->commands[i])
	{
		mini->tkn[i] = assign_number_of_tkn(mini, mini->commands[i]);
		printf("tkn = %d\n", mini->tkn[i]);
		i++;
	}
	mini->tkn[i] = 0;
	mini->tknflag = 1; //potrebbe esse provvisorio, ma ora mi permette di freeare
	//ft_nodes_token(mini->commands, &node)
}

void ft_nodes_token(char **matrix, t_node *node)
{
	node->cmd_path = ft_strdup(*matrix);
	while(*matrix != TOKEN && *matrix != NULL)
	{
		*node->cmd_matrix = ft_strdup(*matrix);
		matrix++;
		ft_lstnew()
	}
	if (matrix)
		node->next = malloc(sizeof(t_node));
	ft_nodes_token(matrix, node->next);
}



void ft_nodes_token(t_mini *mini, t_node *node)
{
	int i;
	int t;

	i = 0;
	t = 0;
	while(mini->commands[i])
	{
		if (mini->tkn[i] >= 10)
		{
			while((!(mini->tkn[i + t] >= 2 && mini->tkn[i + t] <= 7)) || mini->commands[i+t])
				t++;
			node->cmd_matrix = malloc(sizeof(char *) * t);
			node->this_tkn = 20;
			if (ft_is_builtin(mini->commands[i]) != 0)
				node->this_tkn = ft_is_builtin(mini->commands[i]);
			else
				node->cmd_path = ft_command_path(mini->commands[i]);
			node->cmd_matrix[0] = ft_command_path(mini->commands[i]);
		
			if (node->cmd_matrix[0] == 0)
				node->cmd_matrix[0] = ft_strdup(mini->commands[i++]);
			if (i == 1)
				node->left_tkn = NULL;
			else	
				node->left_tkn = mini->tkn[i-1];
			if (!mini->commands[i+t]) 
				node->wright_tkn = NULL;
			else	
				node->wright_tkn = mini->tkn[i+t];
			t = 1;
			while ((!(mini->tkn[i] >= 2 && mini->tkn[i] <= 7)) || mini->commands[i])
				node->cmd_matrix[t++] = ft_strdup(mini->commands[i++]);
			if (mini->commands[i])
				node->next = malloc(sizeof(t_node));
		}
		else if (mini->tkn[i] >= 2 && mini->tkn[i] <= 7)
		{
			node->cmd_matrix = NULL;
		}
			
	}
}
//stringa di char da mettere in ,atrice argomenti
char *find_cmd_or_b_in(t_mini *mini, int pos)
{
	if (mini->tkn[pos] >= 11 && mini->tkn[pos] <= 17)
		return(ft_strdup(mini->commands[pos]));
	else if (mini->tkn[pos] == 20)
		return(ft_command_path(mini->commands[pos]));
	else 
		return (NULL);
}


//conta quanti processi ci sono in una riga, il minimo è 1
int count_commands_pipes(t_mini *mini)
{
	int i;
	int p;

	i = 0;
	p = 1;
	while (mini->commands[i])
	{
		if (mini->commands[i++] == '|')
			p++;
	}
	return (p);
}

// trova la posizione del comando o built in
int find_pos_cmd(t_mini *mini, int p)
{
	int i;
	int z;
	
	i = 1;
	z = 0;
	while (z < p)
	{
		if (mini->commands[i++] == '|')
			z++;
	}
	if (p == 0)
	{
		if (mini->tkn[0] >= 10)
			return (0);
	}
	while (mini->tkn[i])
	{
		if	(mini->tkn[i] >= 10 && !(mini->tkn[i-1] <= 9 && mini->tkn[i-1] >= 3))
			return (i);
		else
			i++;
	}
	return (-1);
}

//conta quanti ergomenti ci sono e quindi quanto allocare
int fill_cmd_count_args(t_mini *mini, int p)
{
	int i;
	int t;

	i = find_pos_cmd(mini, p);
	t = 1;
	while (mini->tkn[i + t] && mini->tkn[i+ t] != 2)
	{
		if	(!(mini->tkn[i+ t -1] <= 9 && mini->tkn[i+ t -1] >= 3) 
			&& !(mini->tkn[i+ t] <= 9 && mini->tkn[i+ t] >= 3))
			t++;
		else
			i++;
	}
	return (t)
}

void set_values_as_null(t_node *node)
{
	node->cmd_path = NULL;
	node->cmd_matrix = NULL;
	node->left_tkn = NULL;
	node->right_tkn = NULL;
	node->this_tkn = NULL;
	node->file = NULL;
	node->next = NULL;
}

//riempe un nodo di tipo comando con tutti gli argomenti
int fill_cmd(t_node *node, t_mini *mini, int p)
{
	int i;
	int t;
	if (ind_pos_cmd(mini, p) != -1)
		i = find_pos_cmd(mini, p);
	else
		return;
	set_values_as_null(node);
	node->cmd_matrix = malloc(sizeof(char *) * fill_cmd_count_args(mini, p) + 1);
	t = 1;
	node->cmd_matrix[0] = find_cmd_or_b_in(mini, i);
	node->cmd_path = find_cmd_or_b_in(mini, i);
	while (mini->tkn[i+t] && mini->tkn[i+t] != 2)
	{
		if	(!(mini->tkn[i+ t - 1] <= 9 && mini->tkn[i+ t - 1] >= 3) 
			&& !(mini->tkn[i+ t] <= 9 && mini->tkn[i+ t] >= 3))
			node->cmd_matrix[t] = ft_strdup(mini->commands[i + t++]);
		else
			i++;
	}//dopo aggiungere anxhe next, next tkn e altri cazzi
	node->cmd_matrix[t] = NULL;
	
}

void fill_redir0(t_node *node, t_mini *mini, int i)
{
	set_values_as_null(node);
	node->this_tkn = mini->tkn[i];
	node->right_tkn = mini->tkn[i + 1];
	if (mini->commands[i-1])
		node->left_tkn = mini->tkn[i - 1];
	node->file = ft_strdup(mini->commands[i+1]);
}

//scorre int tanto quanto serve in base alla pipe
int go_int(t_mini *mini, int p)
{
	int i;
	int z;
	
	i = 0;
	z = 0;
	while (z < p && mini->commands[i])
	{
		if (mini->commands[i++] == '|')
			z++;
	}
	return (i);
}

//mette le redirection sempre
void fill_redir(t_node *tmp, t_mini *mini, int p)
{
	int i;
	int z;

	i = go_int(mini, p);
	z = 0;
	while (mini->tkn[i] && mini->tkn[i] != 2)
	{
		if	(mini->tkn[i] <= 9 && mini->tkn[i] >= 3)
		{
			fill_redir0(tmp, mini, i);
			if (find_pos_cmd(mini, p) != -1)
			{
				tmp->next = malloc(sizeof(t_node));
				tmp = tmp->next;
			}
			else
				tmp->next = NULL;
		}
		i++;
	}
}


//porcodeddio la funzione finale
void fill_nodes(t_node *node, t_mini *mini)
{
	int i;
	int p;
	t_node **cmd_lines;
	
	cmd_lines = malloc(sizeof(t_node *) * count_commands_pipes(mini));
	p = 0;
	while (p != count_commands_pipes(mini))
	{	
		fill_redir(cmd_lines[p], mini, p);
		fill_cmd(cmd_lines[p], mini, p);
		p++;
		if (p != count_commands_pipes(mini))
		{
			node->next = malloc(sizeof(t_node));
			node = node->next;
		}
	}
}
