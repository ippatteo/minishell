/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:24:37 by luca              #+#    #+#             */
/*   Updated: 2024/04/02 08:21:35 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	here_doc(t_node *node, t_mini *mini)
{
	char **matrix;
	char **cmd;
	int	fd[2];
	int	i;

	i = 0;
	if(pipe(fd) == -1)
		ft_putendl_fd(strerror(errno), 2);
	while(1)
	{
		ft_putendl_fd("###ciao", 2);
		matrix[i] = readline("> ");
		if (ft_strcmp(matrix[i], node->file) == 0)
		{
			matrix[i] = NULL;
			break ;
		}
		i++;
	}
	if(dup2(fd[0], mini->curr_input) == -1)
		ft_putendl_fd(strerror(errno), 2);
	if(dup2(fd[1], mini->curr_output) == -1)
		ft_putendl_fd(strerror(errno), 2);
	close(fd[0]);
	close(fd[1]);
}

void	redir_mag(t_node *node, t_mini *mini)
{
	int	fd;

	fd = open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	mini->curr_output = fd;
}

void	redir_magmag(t_node *node, t_mini *mini)
{
	int	fd;

	fd = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	mini->curr_output = fd;
}

void	redir_min(t_node *node, t_mini *mini)
{
	char *path;
	int	fd;

	fd = open(node->file, O_RDONLY);
	if(fd == -1)
	{
		g_exit = 2;
		ft_putendl_fd("no such file or directory", 2);
		return ;
	}
	mini->curr_input = fd;
}


void	redirection_init(t_node *node, t_mini *mini)
{
	if (node->file == NULL)
	{
		g_exit = 2;
		ft_putendl_fd("unexpected token", 2);
		return ;
	}
	if (node->this_tkn == REDIR_MAG)
		redir_mag(node, mini);
	if (node->this_tkn == REDIR_MAGMAG)
		redir_magmag(node, mini);
	if (node->this_tkn == REDIR_MIN)
		redir_min(node, mini);
	if (node->this_tkn == HERE_DOC)
		here_doc(node, mini);
}
void	exec_builtin(t_node *node, t_mini *mini)
{
	if (node->this_tkn == CD)
		ft_cd(node, mini);
	if (node->this_tkn == ECHO)
		ft_echo(node, mini);
	if (node->this_tkn == PWD)
		ft_pwd(node, mini);
	if (node->this_tkn == EXPORT)
		ft_export(node, mini);
	if (node->this_tkn == UNSET)
		ft_unset(mini, node->cmd_matrix);
	if (node->this_tkn == ENV)
		ft_env(node, mini);
	if (node->this_tkn == EXIT)
		ft_exit(node, mini);
}

void	exec_command(t_node *node,t_mini *mini)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		execve(node->cmd_path, node->cmd_matrix, NULL);
	while(waitpid(pid, NULL, 0)>0);
}

void	exec_single(t_node *node, t_mini *mini)
{
	int original_stdin = dup(STDIN_FILENO);
    int original_stdout = dup(STDOUT_FILENO);
	if (mini->curr_input != STDIN_FILENO) 
		dup2(mini->curr_input, STDIN_FILENO);
	if (mini->curr_output != STDOUT_FILENO) 
		dup2(mini->curr_output, STDOUT_FILENO);
	if (node->this_tkn > 10 && node->this_tkn < 20)
		exec_builtin(node, mini);
	if (node->this_tkn == 20)
		exec_command(node, mini);
	if (dup2(original_stdin, STDIN_FILENO) == -1)
		perror("Errore nel ripristinare stdin");
	if (dup2(original_stdout, STDOUT_FILENO) == -1)
		perror("Errore nel ripristinare stdout");
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);	
	if (mini->curr_input != STDIN_FILENO)
	{
		close(mini->curr_input);
		mini->curr_input = STDIN_FILENO; // Reset
	}
	if (mini->curr_output != STDOUT_FILENO)
	{
		close(mini->curr_output);
		mini->curr_output = STDOUT_FILENO; // Reset
	}
}

void	exec(t_node *node, t_mini *mini)
{
	t_node *temp;

	temp = node;
	if (temp == NULL)
		return ;
	while(temp->this_tkn > 2 && temp->this_tkn < 10 && temp->next->right_tkn != PIPE)
	{
		redirection_init(temp, mini);
		temp = temp->next;
	}
	if (!(temp->this_tkn > 2 && temp->this_tkn < 10))
		exec_single(temp, mini);
	//if (temp->left_tkn == -2 && temp->right_tkn == PIPE)
		//pipex(temp, mini);
	return ;
}

/*
void	here_doc(t_node *node, t_mini *mini)
{
	char **matrix;
	char **cmd;
	int	fd[2];
	int	i;

	i = 0;
	if(pipe(fd) == -1)
		ft_putendl_fd(strerror(errno), 2);
	while(1)
	{
		ft_putendl_fd("###ciao", 2);
		matrix[i] = readline("> ");
		if (ft_strcmp(matrix[i], node->file) == 0)
		{
			matrix[i] = NULL;
			break ;
		}
		i++;
	}
	if(dup2(fd[0], mini->curr_input) == -1)
		ft_putendl_fd(strerror(errno), 2);
	if(dup2(fd[1], mini->curr_output) == -1)
		ft_putendl_fd(strerror(errno), 2);
	close(fd[0]);
	close(fd[1]);
}

void	redir_mag(t_node *node, t_mini *mini)
{
	int	fd;

	fd = open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	mini->curr_output = fd;
}

void	redir_magmag(t_node *node, t_mini *mini)
{
	int	fd;

	fd = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	mini->curr_output = fd;
}

void	redir_min(t_node *node, t_mini *mini)
{
	char *path;
	int	fd;

	fd = open(node->file, O_RDONLY);
	if(fd == -1)
	{
		g_exit = 2;
		ft_putendl_fd("no such file or directory", 2);
		return ;
	}
	mini->curr_input = fd;
}


void	redirection_init(t_node *node, t_mini *mini)
{
	if (node->file == NULL)
	{
		g_exit = 2;
		ft_putendl_fd("unexpected token", 2);
		return ;
	}
	if (node->this_tkn == REDIR_MAG)
		redir_mag(node, mini);
	if (node->this_tkn == REDIR_MAGMAG)
		redir_magmag(node, mini);
	if (node->this_tkn == REDIR_MIN)
		redir_min(node, mini);
	if (node->this_tkn == HERE_DOC)
		here_doc(node, mini);
}
void	exec_builtin(t_node *node, t_mini *mini)
{
	if (node->this_tkn == CD)
		ft_cd(node, mini);
	if (node->this_tkn == ECHO)
		ft_echo(node, mini);
	if (node->this_tkn == PWD)
		ft_pwd(node, mini);
	if (node->this_tkn == EXPORT)
		ft_export(node, mini);
	if (node->this_tkn == UNSET)
		ft_unset(mini, node->cmd_matrix);
	if (node->this_tkn == ENV)
		ft_env(node, mini);
	if (node->this_tkn == EXIT)
		ft_exit(node, mini);
}

void	exec_command(t_node *node,t_mini *mini)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		execve(node->cmd_path, node->cmd_matrix, NULL);
	waitpid(pid, NULL, 0);
}

void	exec_single(t_node *node, t_mini *mini)
{
	int original_stdin = dup(STDIN_FILENO);
    int original_stdout = dup(STDOUT_FILENO);
	if (mini->curr_input != STDIN_FILENO) 
	{
		dup2(mini->curr_input, STDIN_FILENO);
		close(mini->curr_input);
	}
	if (mini->curr_output != STDOUT_FILENO) 
	{
		dup2(mini->curr_output, STDOUT_FILENO);
		close(mini->curr_output);
	}
	if (node->this_tkn > 10 && node->this_tkn < 20)
		exec_builtin(node, mini);
	if (node->this_tkn == 20)
		exec_command(node, mini);
	if (dup2(original_stdin, STDIN_FILENO) == -1)
    	perror("Errore nel ripristinare stdin");
    if (dup2(original_stdout, STDOUT_FILENO) == -1)
        perror("Errore nel ripristinare stdout");
	close(original_stdin);
    close(original_stdout);
}

void	executo_d(t_node *node, t_mini *mini)
{
	t_node *temp;
	int fd[2];
	int pid;

	temp = node;
	if (temp == NULL)
		return ;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		while(temp->this_tkn > 2 && temp->this_tkn < 10 && temp->next->right_tkn != PIPE)
		{
			redirection_init(temp, mini);
			temp = temp->next;
		}
		if (!(temp->this_tkn > 2 && temp->this_tkn < 10))
			exec_single(temp, mini);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}


void exec(t_node *node, t_mini *mini)
{
	int p;
	t_node *temp;

	temp = node;
	if (temp == NULL)
		return ;
	p = 0;
	while (p < count_commands_pipes(mini) - 1)
	{
		executo_d(temp, mini);
		temp = temp->next;
		p++;
	}
	while(temp->this_tkn > 2 && temp->this_tkn < 10 && temp->next->right_tkn != PIPE)
		{
			redirection_init(temp, mini);
			temp = temp->next;
		}
	exec_single(temp, mini);
	return;
}
*/