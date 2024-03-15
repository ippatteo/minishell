/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:08:37 by mcamilli          #+#    #+#             */
/*   Updated: 2024/03/12 13:49:06 by luca             ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"

#define BUILTIN 10
#define COMMAND 20
#define PIPE 1
#define END_PIPE -1
#define REDIR_MAG 2
#define REDIR_MAGMAG 4
#define REDIR_MIN 3
#define HERE_DOC 77
#define WORDS 100

extern int g_exit;

typedef struct s_mini
{
	char 	**en;
	int		lines;
	int		*tkn;//array di int che rappresenta i tokens
	int		tknflag;
	char	*sub;
	char	*tmp;
	char	**commands;
	//t_node	*node;
}	t_mini;

typedef struct s_node
{
	struct s_node *next;
	char *cmd_path;
	char **cmd_matrix; //anche la path va qua in pos 0
	int	left_tkn;
	int	right_tkn;
	int type;

}	t_node;

int check_expan_2(t_mini *mini, char **c);
char	*ft_is_file(char *cmd);
int		ft_is_command(char *cmd);
void	ft_tokenizer(t_mini *mini);
void	free_matrix(char **mtr);
char	*ft_getenv(t_mini *mini, char *s);
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
size_t	count_mem(t_mini *mini, char *s);
size_t	split_mem(t_mini *mini, char *s, char **str);
char	**ft_mini_split(t_mini *mini, char *s);
int		lexer(t_mini *mini, char *prompt);


// BUILTINS

void	ft_cd(t_node *node, t_mini *mini);
void	ft_echo(t_node *node, t_mini *mini);
void	ft_pwd(t_node *node, t_mini *mini);
void	ft_env(t_node *node, t_mini *mini);

// EXECUTOR

void	exec(t_node *node, t_mini *mini);
int		pipex(t_node *node);
void	first_pipe(int *fd, t_node *node);
void	right_pipe(int *fd, t_node *node);


#endif
