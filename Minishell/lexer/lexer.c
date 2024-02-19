/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:16:16 by lpicciri          #+#    #+#             */
/*   Updated: 2024/02/16 12:21:59 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// 9 = tab 32 = spazio
int	ft_isspace(char c)
{
	if (c == 9 || c == 32)
		return (0);
	return (1);
}
/*
	prende in input il puntatore all'apice e quale dei due per controllare quando viene
	chiuso contando i caratteri all'interno
*/
size_t	count_mem_quote(char *str, char c)
{
	size_t	mem;

	mem = 1;
	str++;
	while(*str && *str != c)
	{
		mem++;
		str++;
	}
	if (*str == '\0')
		return(0);
	mem++;
	return (mem);
}

// rimuove gli spazi finali se ci sono e cambia il terminatore dopo l'ultimo carattere

char *clear_last_spaces(char *str)
{
	int	i;

	i = 0;
	while(str[i] != '\0')
		i++;
	while (ft_isspace(str[i - 1]) == 0)
		i--;
	str[i] = '\0';
	return (str);
}

// conta la memoria da allocare per la matrice

size_t	count_mem(char *str)
{
	size_t	mem;
	size_t	quote_mem;

	mem = 0;
	while(*str)
	{
		quote_mem = 0;
		if (ft_isspace(*str) != 0 && *str != QUOTE && *str != D_QUOTE)
			mem++;
		if (*str == QUOTE || *str == D_QUOTE)
		{
			quote_mem = count_mem_quote(str, *str);
			mem += quote_mem;
			str += quote_mem;
		}
		while(ft_isspace(*str) == 0)
		{
			mem += 1;
			while(ft_isspace(*str) == 0)
				str++;
		}
		str++;
	}
	return (mem + 1);
}

// splitta il prompt in una matrice

char **ft_split(char *str)
{
	char **s = NULL;
	int	i;
	size_t	mem;

	i = 0;
	mem = 0;
	while(ft_isspace(*str) == 0)
		str++;
	str = clear_last_spaces(str);
	mem = count_mem(str);
	if (mem == 0)
	{
		printf("mem error\n");
		return(NULL);
	}
	printf("%zu\n", count_mem(str));
	return(s);
}

// chiama la split

int	lexer(char *prompt)
{
	char **cmd_split;

	//pulisce spazi
	cmd_split = ft_split(prompt);
	if (cmd_split == NULL)
		return (-1);
	return(0);
}
