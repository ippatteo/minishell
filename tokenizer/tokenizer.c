/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:42:15 by lpicciri          #+#    #+#             */
/*   Updated: 2024/04/02 14:48:02 by lpicciri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"
/*
legenda:
n = 1 (è file)
n = 111	(è argomento)
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
int ft_is_command(t_mini *mini, char *cmd)
{
	char	*path;
	char	**folders;
	char	*tmp;
	int		i;

	i = 0;
	if(access(cmd , X_OK) == 0)
		return (1);
	if (ft_getenv(mini->en, "PATH") == NULL)
		return (0);
	folders = ft_split(ft_getenv(mini->en, "PATH"), ':');
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

int assign_number_of_tkn(t_mini *mini, char *cmd)
{
	if (ft_is_builtin(cmd) != 0)
		return (ft_is_builtin(cmd));
	else if (ft_is_pipe_redir_hd(cmd))
		return(ft_is_pipe_redir_hd(cmd));
	else if (ft_is_command(mini, cmd))
		return (20);
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
	return (1);

}
int go_int(t_mini *mini, int p)
{
	int i;
	int z;

	i = 0;
	z = 0;
	while (z < p && mini->commands[i])
	{
		if (mini->tkn[i] == PIPE)
			z++;
		i++;
	}
	return (i);
}

//stringa di char da mettere in matrice argomenti
char *find_cmd_or_b_in(t_mini *mini, int pos)
{
	if (mini->tkn[pos] >= 11 && mini->tkn[pos] <= 17)
		return(ft_strdup(mini->commands[pos]));
	else if (mini->tkn[pos] == 20)
		return(ft_command_path(mini, mini->commands[pos]));
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
		if (mini->tkn[i] == PIPE)
			p++;
		i++;
	}
	return (p);
}

// trova la posizione del comando o built in
int find_pos_cmd(t_mini *mini, int p)
{
	int i;
	int z;

	i = go_int(mini, p);
	z = 0;
	while (mini->tkn[i] && mini->tkn[i] != PIPE)
	{
		if	(mini->tkn[i] >= BUILTIN && mini->tkn[i] <= COMMAND || mini->tkn[i] == ARGS)
			return (i);
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
	t = 0;
	while (mini->tkn[i] && mini->tkn[i] != PIPE)
	{
		if	(mini->tkn[i] == ARGS)
			t++;
		i++;
	}
	return (t);
}

void set_values_as_null(t_node *node)
{
	node->cmd_path = NULL;
	node->cmd_matrix = NULL;
	node->left_tkn = 0;
	node->right_tkn = 0;
	node->this_tkn = 0;
	node->file = NULL;
	node->next = NULL;
	node->error = 0;
	node->n_pipe = -1;
}

int set_fill_error(t_node *new, t_mini *mini, int p, int i)
{
	int t;

	t = 1;
	new->n_pipe = p;
	if (mini->tkn[i] == ARGS)
	{
		new->error = 127;
		new->cmd_path = ft_strdup(mini->commands[i]);
		return (1);
	}
	else
	{
		new->cmd_matrix = ft_calloc(sizeof(char *), fill_cmd_count_args(mini, p) + 2);
		t = 1;
		new->cmd_matrix[0] = find_cmd_or_b_in(mini, i);
		new->cmd_path = find_cmd_or_b_in(mini, i);
		while (mini->tkn[i] && mini->tkn[i] != PIPE)
		{
			if	(mini->tkn[i] == ARGS)
				new->cmd_matrix[t++] = ft_strdup(mini->commands[i]);
			i++;
		}
		new->cmd_matrix[t] = NULL;
		return (0);
	}
}

int there_is_pipe(t_mini *mini, int i)
{
	while (mini->tkn[i])
	{
		if (mini->tkn[i] == PIPE)
			return (PIPE);
		i++;
	}
	return(END_PIPE);
}
void fill_cmd(t_node **node, t_mini *mini, int p)
{
	int i;
	int t;
	t_node *new;

	if (find_pos_cmd(mini, p) == -1)
		return;
	i = find_pos_cmd(mini, p);
	new = (t_node *)ft_calloc(sizeof(t_node), 1);
	set_values_as_null(new);
	new->this_tkn = mini->tkn[i];
	new->right_tkn =  there_is_pipe(mini, i);
	if (p)
		new->left_tkn = PIPE;
	else
		new->left_tkn = START_P;
	if (set_fill_error(new, mini, p, i))
	{
		ft_lstadd_back(node, new);
		return;
	}
	ft_lstadd_back(node, new);
}

//filla e controlla se c'è il file, se c'è ben altrimenti sull'errore mette 2,
//l'unico morivo per cui mette 2 qua è unexpected token
void fill_redir0(t_node *new, t_mini *mini, int i, int p)
{
	set_values_as_null(new);
	new->this_tkn = mini->tkn[i];
	if (mini->tkn[i + 1] && mini->tkn[i + 1] != PIPE)
		mini->tkn[i + 1] = 1;
	else
	{
		new->error = 2;//unexpected token
		return ;
	}
	new->right_tkn = mini->tkn[i + 1];
	new->n_pipe = p;
	new->file = ft_strdup(mini->commands[i+1]);
}

//mette le redirection sempre
void fill_redir(t_node **node, t_mini *mini, int p)
{
	int i;
	int z;
	t_node *new;

	i = go_int(mini, p);
	z = 0;

	while (mini->tkn[i] && mini->tkn[i] != PIPE)
	{
		if	(mini->tkn[i] <= HERE_DOC && mini->tkn[i] >= REDIR_MIN)
		{

			new = (t_node *)ft_calloc(sizeof(t_node), 1);
			fill_redir0(new, mini, i, p);
			ft_lstadd_back(node, new);
		}
		i++;
	}
}


//porcodeddio la funzione finale

void ft_free_tnodes(t_node *node)
{
	t_node* temp;
	if (node == NULL)
		return ;
	while (node != NULL)
	{
		temp = node;
		node = node->next;
		if (temp->cmd_matrix != NULL)
			free_matrix(temp->cmd_matrix);
		if (temp->cmd_path != NULL)
			free(temp->cmd_path);
		if (temp->file != NULL)
			free(temp->file);
		free(temp);
	}
}



int fill_nodes(t_node **node, t_mini *mini)
{
	int i;
	int p;

	p = 0;
	if (!ft_tokenizer(mini))
		return(0);
	if (*node != NULL)
	{
		ft_free_tnodes(*node);
		*node = NULL;
	}
	while (p < count_commands_pipes(mini))
	{
		fill_redir(node, mini, p);
		fill_cmd(node, mini, p);
		p++;
	}
	return(1);
}
