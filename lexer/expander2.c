/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 20:15:45 by mcamilli          #+#    #+#             */
/*   Updated: 2024/04/11 13:55:39 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	check_for_quotes(char *str)
{
	while (*str)
	{
		if (*str == QUOT || *str == D_QUOT)
			return (1);
		str++;
	}
	return (0);
}

int	str_quot_count_2(t_mini *mini, char *str)
{
	int		mem;
	char	c;

	mem = 0;
	c = 0;
	while (*str)
	{
		if (*str == 39 || *str == 34)
		{
			c = *str;
			str++;
			while (*str != c)
			{
				str++;
				mem++;
			}
			str++;
		}
		else
		{
			str++;
			mem++;
		}
	}
	return (mem);
}

char	*str_quot_realloc_2(t_mini *mini, char *str)
{
	char	*orig;
	char	*tmp;
	char	c;

	c = 0;
	orig = ft_calloc(sizeof(char), str_quot_count_2(mini, str) + 1);
	tmp = orig;
	while (*str)
	{
		if (*str == 39 || *str == 34)
		{
			c = *str;
			str++;
			while (*str != c)
				*(orig++) = *(str++);
			str++;
		}
		else
			*(orig++) = *(str++);
	}
	*orig = '\0';
	return (tmp);
}

int	check_quot_2(t_mini *mini, char **c)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (c[i])
	{
		if (check_for_quotes(c[i]))
		{
			tmp = str_quot_realloc_2(mini, c[i]);
			swapstrings(&c[i], &tmp);
			free(tmp);
			i++;
		}
		else
			i++;
	}
	return (i);
}
