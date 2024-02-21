/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:16:16 by lpicciri          #+#    #+#             */
/*   Updated: 2024/02/21 18:45:03 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"
void ft_printmap(char **c)
{
	int x;

	x = 0;
	//write(1, "\n", 1);
	while (c[x])
	{
		ft_putstr(c[x]);
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
	ft_printmap(mini->commands);
	return(0);
}
