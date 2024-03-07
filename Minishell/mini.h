/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:08:37 by mcamilli          #+#    #+#             */
/*   Updated: 2024/03/07 16:09:57 by mcamilli         ###   ########.fr       */
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
# include "libft/libft.h"

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
}	t_mini;

typedef struct s_redpipe
{
	int r_p; //che red o pipe è
	void *input;
	void *output;
}	t_redpipe;

typedef struct s_cmdorbin
{
	int cmd_in; //che comando o builtin è
	char **cmd_args; 
	void *input;
	void *output;
	
}	t_cmdorbin;

char *ft_is_file(char *cmd);
char *ft_is_command(char *cmd);
void ft_tokenizer(t_mini *mini);
void free_matrix(char **mtr);
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




#endif
