/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:16:16 by lpicciri          #+#    #+#             */
/*   Updated: 2024/02/22 15:38:32 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void ft_printmap0(char **c)
{
	int x;

	x = 0;
	while (c[x])
	{
		if(ft_putstr(c[x]));
			write(1, " ", 1);
		x++ ;
	}
	write(1, "\n", 1);
}
void ft_printmap(t_mini *mini, char **c)
{
	int x;

	x = 0;
	//write(1, "\n", 1);
	while (x < mini->lines)
	{
		if(ft_putstr(c[x]));
			write(1, " ", 1);
		x++ ;
	}
	write(1, "\n", 1);
}

int	lexer(t_mini *mini, char *prompt)
{
	if (mini->commands != NULL)
		free(mini->commands);
	mini->commands = ft_mini_split(prompt);
	if (mini->commands == NULL)
		return (0);
	ft_printmap0(mini->commands);
	mini->lines = check_expan(mini->commands);
	ft_printmap(mini, mini->commands);
	return(0);
}