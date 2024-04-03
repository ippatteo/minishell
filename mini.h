/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:08:37 by mcamilli          #+#    #+#             */
/*   Updated: 2024/04/03 19:01:41 by lpicciri         ###   ########.fr       */
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
# include <sys/stat.h>
# include "libft/libft.h"
# include <signal.h>

# define BUILTIN 10
# define ECHO 11
# define CD 12
# define PWD 13
# define EXPORT 14
# define UNSET 15
# define ENV 16
# define EXIT 17
# define BUILTIN 10
# define COMMAND 20
# define PIPE 2
# define REDIR_MAG 7
# define REDIR_MAGMAG 4
# define REDIR_MIN 3
# define HERE_DOC 9
# define FILE 1
# define ARGS 111
# define D_QUOT 34
# define QUOT 39
# define END_PIPE 222
# define START_P -2

# define CRED "\e[0;31m"
# define RESET "\001\e[0m\002"

extern int	g_exit;

typedef struct s_mini
{
	char	**en;
	int		lines;
	char	*tkn;
	int		tknflag;
	char	*sub;
	char	*tmp;
	char	**commands;
	int		curr_input;
	int		curr_output;
	int		temp_in;
	int		temp_out;
	//t_node	*node;
}	t_mini;

typedef struct s_node
{
	struct s_node	*next;
	char			*cmd_path;
	char			**cmd_matrix;
	int				left_tkn;
	int				right_tkn;
	int				error;
	int				this_tkn;
	char			*file;
	int				n_pipe;
}	t_node;

int		ft_exp_qutes(char *c);
void	init(t_mini *mini, t_node *node);
int		fill_nodes(t_node **node, t_mini *mini);
void	fill_redir(t_node **node, t_mini *mini, int p);
void	fill_redir0(t_node *new, t_mini *mini, int i, int p);
void	fill_cmd(t_node **node, t_mini *mini, int p);
int		cmd_error(t_mini *mini, t_node *new, int i);
int		there_is_pipe(t_mini *mini, int i);
int		set_fill_error(t_node *new, t_mini *mini, int p, int i);
void	set_values_as_null(t_node *node);
int		fill_cmd_count_args(t_mini *mini, int p);
int		find_pos_cmd(t_mini *mini, int p);
int		count_commands_pipes(t_mini *mini);
char	*find_cmd_or_b_in(t_mini *mini, int pos);
int		go_int(t_mini *mini, int p);
int		ft_tokenizer(t_mini *mini);
char	*ft_command_path(t_mini *mini, char *cmd);
int		assign_number_of_tkn(t_mini *mini, char *cmd);
int		ft_is_command(t_mini *mini, char *cmd);
int		ft_is_pipe_redir_hd(char *cmd);
char	*ft_strdup_slash(const char *str);
int		ft_is_builtin(char *cmd);
int		str_exp_count(t_mini *mini, char *str);
int		ft_it_is_exp_valid(t_mini *mini, char *s);
int		count_exp(char *str);
void	sig_handle(int signum);
void	signal_heredoc(void);
int		ft_exp_count_qutes(char *c);
int		redirection_init(t_node *node, t_mini *mini);
int		check_space(char *str, t_node *node, t_mini *mini);
int		redir_min(t_node *node, t_mini *mini);
void	redir_magmag(t_node *node, t_mini *mini);
void	redir_mag(t_node *node, t_mini *mini);
void	here_doc(t_node *node, t_mini *mini);
void	ft_close_all(t_mini *mini);
void	exec_single(t_node *node, t_mini *mini);
void	exec_command(t_node *node, t_mini *mini);
void	exec_builtin(t_node *node, t_mini *mini);
int		is_there_redir(t_mini *mini);
void	ft_close_all(t_mini *mini);
int		count_commands_pipes(t_mini *mini);
int		check_pipe_errors(t_mini *mini);
int		err_quote(t_mini *mini);
void	ft_free_tnodes(t_node *node);
void	ft_printmap0(char **c);
void	realloc_quotes(t_mini *mini);
int		check_errors(t_mini *mini);
int		ft_lstsize(t_node *lst);
void	ft_lstadd_back(t_node **lst, t_node *new);
void	ft_lstadd_front(t_node **lst, t_node *new);
t_node	*ft_lstlast(t_node *lst);
void	ft_lstadd_back(t_node **lst, t_node *new);
int		fill_nodes(t_node **node, t_mini *mini);
void	ft_printnode(t_node *node);
int		check_expan_2(t_mini *mini, char **c);
char	*ft_is_file(char *cmd);
int		ft_is_command(t_mini *mini, char *cmd);
int		ft_tokenizer(t_mini *mini);
void	free_matrix(char **mtr);
int		check_env(char c, char d);
char	*ft_getenv(char **en, char *s);
int		count_matrix(char **matrix);
void	copy_env(t_mini *mini, char **e);
char	*str_exp_realloc(t_mini *mini, char *str);
int		str_exp_count(t_mini *mini, char *str);
int		count_exp(char *str);
int		ft_it_is_exp_valid(t_mini *mini, char *s);
char	*ft_substr0(char *s, int len);
void	swapstrings(char **str1, char **str2);
void	copy_env(t_mini *mini, char **e);
void	ft_printmap(t_mini *mini, char **c);
int		check_expan(t_mini *mini, char **c);
int		count_mem_quote(char *str, char c);
int		count_quot_pipe_redir(char *str, char c);
int		count_words(char *str);
void	ft_printmap1(char **c);
size_t	count_mem(t_mini *mini, char *s);
size_t	split_mem(t_mini *mini, char *s, char **str);
char	**ft_mini_split(t_mini *mini, char *s);
int		lexer(t_mini *mini, char *prompt);
void	ft_exit_all(t_node *node, t_mini *mini);
void	ft_free_tnodes(t_node *node);
void	signal_handler(void);

// BUILTINS

void	ft_cd(t_node *node, t_mini *mini);
void	ft_echo(t_node *node, t_mini *mini);
void	ft_pwd(t_node *node, t_mini *mini);
void	ft_env(t_node *node, t_mini *mini);
void	ft_export(t_node *node, t_mini *mini);
void	ft_unset(t_mini *mini, char **mtr);
int		ft_isspace(int c);
void	ft_exit(t_node *node, t_mini *mini);

// EXECUTOR

void	exec(t_node *node, t_mini *mini);
int		pipex(t_node *node, t_mini *mini);
void	here_doc(t_node *node, t_mini *mini);

#endif
