/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 20:15:45 by mcamilli          #+#    #+#             */
/*   Updated: 2024/04/07 21:45:04 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"
int check_for_expan(char *str)
{
	while (*str)
	{
		if (check_env(*str, *(str + 1)) != -1)
			return (1);
		str++;
	}
	return (0);
}

int	check_expan(t_mini *mini, char **c)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (c[i])
	{
		if (check_for_expan(c[i]))
		{
			tmp = str_exp_realloc(mini, c[i]);
			swapstrings(&c[i], &tmp);
			free(tmp);
			i++;
		}
		else
			i++;
	}
	return (i);
}

int	str_exp_count_2(t_mini *mini, char *str, char *sub)
{
	int	mem;

	mem = 0;
	while (*str)
	{
		semaphore_quotes(*str, mini);
		if (*str == '$' && *(str + 1) == '?' && !mini->open_quot)
		{
			str += 2;
			mem += ft_strlen(sub);
		}
		else
		{
			str++;
			mem++;
		}
	}
	return (mem);
}

char	*str_exp_realloc_2(t_mini *mini, char *str)
{
	char	*sub;
	char	*orig;
	char	*tmp;

	sub = ft_itoa(g_exit);
	orig = ft_calloc(sizeof(char), str_exp_count_2(mini, str, sub) + 1);
	tmp = orig;
	while (*str)
	{
		semaphore_quotes(*str, mini);
		if (*str == '$' && *(str + 1) == '?' && !mini->open_quot)
		{
			ft_strlcpy(orig, sub, 8);
			orig += ft_strlen(sub);
			str += 2;
		}
		else
			*(orig++) = *(str++);
	}
	free(sub);
	*orig = '\0';
	return (tmp);
}

int	check_expan_2(t_mini *mini, char **c)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (c[i])
	{
		if (ft_strnstr(c[i], "$?", ft_strlen(c[i])))
		{
			tmp = str_exp_realloc_2(mini, c[i]);
			swapstrings(&c[i], &tmp);
			free(tmp);
			i++;
		}
		else
			i++;
	}
	return (i);
}

int	check_env(char c, char d)
{
	if (c == '$' && d && (ft_isalnum(d) || ft_isalpha(d) || d == '_'))
		return (0);
	return (-1);
}
