/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:16:16 by lpicciri          #+#    #+#             */
/*   Updated: 2024/03/02 15:52:03 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

//conta il numero di char dentro una matrice + i null

void ft_printmap0(char **c)
{
	int x;

	x = 0;
	while (c[x])
	{
		if(ft_putstr(c[x]))
			write(1, "\n", 1);
		x++ ;
	}
	write(1, "\n", 1);
	write(1, "\n", 1);
}

void copy_env(t_mini *mini, char **e)
{
	int i;

	i = 0;
	mini->en = ft_calloc((count_matrix(e) + 1), sizeof (char *));
	while(e[i])
	{
		mini->en[i] = ft_strdup(e[i]);
		i++;
	}
	mini->en[i] = 0;
	ft_printmap0(mini->en);
}

void ft_printmap1(t_mini *mini, char **c)
{
	int x;

	x = 0;
	while (c[x])
	{
		if(ft_putstr(c[x]))
			write(1, "\n", 1);
		x++ ;
	}
	mini->lines = x;
	write(1, "\n", 1);
}

void free_matrix(char **mtr)
{
	int i;

	i = 0;
	while (mtr[i])
	{
		free(mtr[i]);
		i++;
	}
}
int	lexer(t_mini *mini, char *prompt)
{
	if (mini->commands != NULL)
		free_matrix(mini->commands);
	mini->commands = ft_mini_split(prompt);
	if (mini->commands == NULL)
		return (0);
	ft_printmap1(mini, mini->commands);
	mini->lines = check_expan(mini->commands);
	ft_printmap1(mini, mini->commands);
	return(0);
}