/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 20:15:45 by mcamilli          #+#    #+#             */
/*   Updated: 2024/03/18 16:03:32 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

//conta dall'expander quanti caratteri ci sono, serve al substr
//ma deve esser fatto partire da dopo il $



//conta quanti caratteri contengono le virgolette, virgolette comprese
int	count_mem_quote(char *str, char c)
{
	int	mem;

	mem = 1;
	str++;
	while(*str && *str != c)
	{
		mem++;
		str++;
	}
	if (*str == '\0')
	{
		return (mem);
	}
	mem++;
	return (mem);
}
//conta quansiasi cosa non sia una parola, virgolette, pipe e redirection
int count_quot_pipe_redir(char *str, char c)
{
	if (c == '<' || c =='>')
	{
		++str;
		if (*str == c)
			return (2);
		else
			return (1);
	}
	else if (c == '|')
	{
		++str;
		return (1);
	}
	else if ((*str == 34) || (*str == 39))
		return (count_mem_quote(str, c));
	else
		return (0);
}
//conta quanti char ci sono in una parola "normale"
int	count_words(char *str)
{
	int mem;

	mem = 0;
	while (*str)
	{
		if ((*str == '>') || (*str == '<')
			|| (*str == '|') || (*str == 34) || (*str == 39) || (*str == ' '))
				break ;
		else
		{
			str++;
			mem++;
		}
	}
	return (mem);
}

//conta quanta memoria bisogna allocare aggiungendo il +1 del \0 ogni colta
//restituisce 0 in caso di syntax error
size_t	count_mem(t_mini *mini, char *s)
{
	int mem;

	mem = 0;
	while (*s)
	{
		if ((*s == '>') || (*s == '<')
			|| (*s == '|') || (*s == 34) || (*s == 39))
		{
			mem += count_quot_pipe_redir(s, *s) + 1;
			if (!count_quot_pipe_redir(s, *s))
				return (-1);
			s += count_quot_pipe_redir(s, *s);
		}
		else if (*s == ' ' || *s == '	' )
			s++;
		else if (ft_it_is_exp_valid(mini, s))
			s += ft_it_is_exp_valid(mini, s);
		else
		{
			mem += count_words(s) + 1;
			s += count_words(s);
		}
	}
	return (mem);
}

//una volta allocata la memoria giusta riempe la matrice
size_t	split_mem(t_mini *mini, char *s, char **str)
{
	int i;

	i = 0;
	while (*s)
	{
		if ((*s == '>') || (*s == '<')
			|| (*s == '|') || (*s == 34) || (*s == 39))
		{
			str[i] = ft_substr(s, 0, count_quot_pipe_redir(s, *s));
			s += count_quot_pipe_redir(s, *s);
			i++;
		}
		else if (*s == ' ' || *s == '	')
			s++;
		else if (ft_it_is_exp_valid(mini, s))
			s += ft_it_is_exp_valid(mini, s);
		else
		{
			str[i] = ft_substr(s, 0, count_words(s));
			s += count_words(s);
			i++;
		}
	}
	str[i] = NULL;
	return (i);
}

