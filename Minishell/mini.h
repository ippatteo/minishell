/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:08:37 by mcamilli          #+#    #+#             */
/*   Updated: 2024/02/23 13:21:20 by mcamilli         ###   ########.fr       */
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
# include "printf/ft_printf.h"
typedef struct s_mini
{
	char 	**en;
	int		lines;
	char	*sub; //serve in ft_exp (forse)
	char	*tmp;
	char	**commands;
}	t_mini;

void	copy_env(t_mini *mini, char **e);
void	ft_printmap(t_mini *mini, char **c);
int		check_expan(char **c);
int		count_mem_quote(char *str, char c);
int		count_quot_pipe_redir(char *str, char c);
int		count_words(char *str);
size_t	count_mem(char *s);
size_t	split_mem(char *s, char **str);
char	**ft_mini_split(char *s);
int		lexer(t_mini *mini, char *prompt);




#endif
