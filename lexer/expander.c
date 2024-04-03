/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 20:15:45 by mcamilli          #+#    #+#             */
/*   Updated: 2024/04/03 17:17:55 by lpicciri         ###   ########.fr       */
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

	tmp = NULL;
	if (*s == '$' && *(s + 1) == '?')
		return (0);
	if (!(*s == '$' && (ft_isalnum (*(s +1))
				|| ft_isalpha (*(s +1)) || *(s +1) == '_')))
		return (0);
	tmp = ft_substr(s, 1, count_exp(s + 1));
	if (!ft_getenv(mini->en, tmp))
	{
		free(tmp);
		return (count_exp(s + 1) + 1);
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
		if (*str == '$' && (ft_isalnum (*(str + 1))
				|| ft_isalpha (*(str + 1)) || *(str + 1) == '_'))
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

	mini->sub = NULL;
	orig = ft_calloc(sizeof(char), str_exp_count(mini, str) + 1);
	tmp = orig;
	while (*str)
	{
		if (check_env(*str, *(str + 1)) == 0)
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
