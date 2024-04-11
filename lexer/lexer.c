/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:16:16 by lpicciri          #+#    #+#             */
/*   Updated: 2024/04/11 13:57:00 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	ft_printmap0(char **c)
{
	int	x;

	x = 0;
	if (c == NULL)
	{
		write(2, "NULL\n", 5);
		return ;
	}
	while (c[x])
	{
		if (ft_putstr(c[x]))
			write(1, "\n", 1);
		x++ ;
	}
}

void	copy_env(t_mini *mini, char **e)
{
	int	i;

	i = 0;
	mini->en = ft_calloc((count_matrix(e) + 1), sizeof(char *));
	if (!mini->en)
		return ;
	while (e[i])
	{
		mini->en[i] = ft_strdup(e[i]);
		i++;
	}
	mini->en[i] = NULL;
}

void	ft_printmap1(char **c)
{
	int	x;

	x = 1;
	printf("%s\n", c[0]);
	while (c[x])
	{
		if (ft_putstr (c[x]))
			write(1, "\n", 1);
		x++ ;
	}
	write(1, "\n", 1);
}

void	free_matrix(char **mtr)
{
	int	i;

	i = 0;
	if (mtr == NULL)
		return ;
	if (mtr != NULL)
	{
		while (mtr[i] != NULL)
		{
			free(mtr[i]);
			i++;
		}
		free(mtr);
	}
}

int	lexer(t_mini *mini, char *prompt)
{
	if (!no_open_quote(prompt))
		return (0);
	if (mini->commands != NULL)
		free_matrix(mini->commands);
	mini->commands = ft_mini_split(mini, prompt);
	if (mini->commands[0] == NULL)
		return (0);
	check_expan(mini, mini->commands);
	check_expan_2(mini, mini->commands);
	mini->lines = check_quot_2(mini, mini->commands);
	return (1);
}
