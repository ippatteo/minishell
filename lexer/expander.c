/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 20:15:45 by mcamilli          #+#    #+#             */
/*   Updated: 2024/04/11 14:05:45 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_exp_count_qutes(char *c)
{
	int	i;

	i = 0;
	while (c[i] && c[i] != '=')
		i++;
	return (i);
}

int	count_exp(char *str)
{
	int	mem;

	mem = 0;
	while (*str)
	{
		if (!(ft_isalnum(*str) || ft_isalpha(*str) || *str == '_'))
			break ;
		else
		{
			str++;
			mem++;
		}
	}
	return (mem);
}

int	ft_it_is_exp_valid(t_mini *mini, char *s)
{
	char	*tmp;
	int		q;

	tmp = NULL;
	q = 0;
	if (*s == D_QUOT)
		q = count_mem_quote(s++, D_QUOT);
	if (q == 2)
		return (2);
	if (*s == '$' && *(s + 1) == '?')
		return (0);
	if (!(*s == '$' && (ft_isalnum (*(s +1))
				|| ft_isalpha (*(s +1)) || *(s +1) == '_')))
		return (0);
	tmp = ft_substr(s, 1, count_exp(s + 1));
	if (!ft_getenv(mini->en, tmp))
	{
		free(tmp);
		return (ft_it_is_exp_valid_2(q, count_exp(s + 1)));
	}
	else
	{
		free(tmp);
		return (0);
	}
}

int	str_exp_count(t_mini *mini, char *str)
{
	char	*tmp;
	int		mem;

	tmp = NULL;
	mem = 0;
	while (*str)
	{
		semaphore_quotes(*str, mini);
		if (check_env(*str, *(str + 1)) != -1 && !mini->open_quot)
		{
			tmp = ft_substr((const char *)str, 1, count_exp(str + 1));
			if (ft_getenv(mini->en, tmp))
				mem += ft_strlen(ft_getenv(mini->en, tmp));
			str += ft_strlen(tmp) + 1;
			free(tmp);
		}
		else
		{
			mem++;
			str++;
		}
	}
	return (mem);
}

char	*str_exp_realloc(t_mini *mini, char *str)
{
	char	*orig;
	char	*tmp;

	orig = ft_calloc(sizeof(char), str_exp_count(mini, str) + 1);
	tmp = orig;
	while (*str)
	{
		semaphore_quotes(*str, mini);
		if (check_env(*str, *(str + 1)) == 0 && mini->open_quot == 0)
		{
			mini->sub = ft_substr0(str + 1, count_exp(str + 1));
			if (ft_getenv(mini->en, mini->sub))
			{
				ft_strlcpy(orig, ft_getenv(mini->en, mini->sub),
					ft_strlen(ft_getenv(mini->en, mini->sub)) + 1);
				orig += ft_strlen(ft_getenv(mini->en, mini->sub));
			}
			str += ft_strlen(mini->sub) + 1;
			free (mini->sub);
		}
		else
			*(orig++) = *(str++);
	}
	*orig = '\0';
	return (tmp);
}
