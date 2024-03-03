/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:08:37 by mcamilli          #+#    #+#             */
/*   Updated: 2024/03/03 22:33:39 by mcamilli         ###   ########.fr       */
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

typedef struct s_mini
{
	char 	**en;
	int		lines;
	char	*sub; //serve in ft_exp (forse)
	char	*tmp;
	char	**commands;
}	t_mini;

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
