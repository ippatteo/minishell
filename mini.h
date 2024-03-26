/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:08:37 by mcamilli          #+#    #+#             */
/*   Updated: 2024/03/26 18:24:39 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <time.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <signal.h>

#define END_PIPE -1
#define BUILTIN 10
#define ECHO 11
#define CD 12
#define PWD 13
#define EXPORT 14
#define UNSET 15
#define ENV 16
#define EXIT 17
#define BUILTIN 10
#define COMMAND 20
#define PIPE 2
#define REDIR_MAG 7
#define REDIR_MAGMAG 4
#define REDIR_MIN 3
#define HERE_DOC 9
#define FILE 1
#define ARGS 111
#define D_QUOT 34
#define QUOT 39

#define CRED "\e[0;31m"
#define RESET "\001\e[0m\002"

extern int g_exit;

typedef struct s_mini
{
	char 	**en;
	int		lines;
	char	*tkn;//array di int che rappresenta i tokens
	int		tknflag;//capisce se la memoria per tkn è stat mai allocata
	char	*sub;
	char	*tmp;
	char	**commands;
	int		curr_input;
	int		curr_output;
	//t_node	*node;
}	t_mini;

typedef struct s_node
{
	struct s_node *next;
	char *cmd_path;
	char **cmd_matrix; //anche la path va qua in pos 0
	int left_tkn;
	int	right_tkn;
	int this_tkn;
	char *file;
}	t_node;


void ft_free_tnodes(t_node *node);
void ft_printmap0(char **c);
void realloc_quotes(t_mini *mini);
int check_errors(t_mini *mini);
int	ft_lstsize(t_node *lst);
void	ft_lstadd_back(t_node **lst, t_node *new);
void	ft_lstadd_front(t_node **lst, t_node *new);
t_node	*ft_lstlast(t_node *lst);
void	ft_lstadd_back(t_node **lst, t_node *new);
int		fill_nodes(t_node **node, t_mini *mini);
void ft_printnode(t_node *node);
int check_expan_2(t_mini *mini, char **c);
char	*ft_is_file(char *cmd);
int ft_is_command(t_mini *mini, char *cmd);
int		ft_tokenizer(t_mini *mini);
void	free_matrix(char **mtr);
char	*ft_getenv(char **en, char *s);
int		count_matrix(char **matrix);
void 	copy_env(t_mini *mini, char **e);
char	*str_exp_realloc(t_mini *mini, char *str);
int		str_exp_count(t_mini *mini, char *str);
int		count_exp(char *str);
int		ft_it_is_exp_valid(t_mini *mini, char *s);
char	*ft_substr0(char *s, int len);
void	swapStrings(char **str1, char **str2);
void	copy_env(t_mini *mini, char **e);
void	ft_printmap(t_mini *mini, char **c);
int		check_expan(t_mini *mini, char **c);
int		count_mem_quote(char *str, char c);
int		count_quot_pipe_redir(char *str, char c);
int		count_words(char *str);
void ft_printmap1(char **c);
size_t	count_mem(t_mini *mini, char *s);
size_t	split_mem(t_mini *mini, char *s, char **str);
char	**ft_mini_split(t_mini *mini, char *s);
int		lexer(t_mini *mini, char *prompt);
void ft_exit_all(t_node *node, t_mini *mini);
void ft_free_tnodes(t_node *node);

void	signal_handler();

// BUILTINS

void	ft_cd(t_node *node, t_mini *mini);
void	ft_echo(t_node *node, t_mini *mini);
void	ft_pwd(t_node *node, t_mini *mini);
void	ft_env(t_node *node, t_mini *mini);
void	ft_export(t_node *node, t_mini *mini);
void ft_unset(t_mini *mini, char **mtr);
int		ft_isspace(int c);
void	ft_exit(t_node *node, t_mini *mini);

// EXECUTOR

void	exec(t_node *node, t_mini *mini);
int	pipex(t_node *node, t_mini *mini);
void	here_doc(t_node *node, t_mini *mini);

#endif
