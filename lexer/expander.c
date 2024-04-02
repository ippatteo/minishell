/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 20:15:45 by mcamilli          #+#    #+#             */
/*   Updated: 2024/04/02 20:07:19 by lpicciri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	*ft_getenv(char **en, char *s)
{
	int		i;
	char	*str;

	i = 0;
	while (en[i])
	{
		if (ft_strnstr(en[i], s, ft_strlen(s)))
		{
			str = ft_strnstr(en[i], s, ft_strlen(s));
			return (str + ft_strlen(s) + 1);
		}
		else
			i++;
	}
	return (NULL);
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
	if (!(*s == '$' && (ft_isalnum(*(s + 1)) || ft_isalpha(*(s + 1))
				|| *(s + 1) == '_')))
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
		if (*str == '$' && (ft_isalnum(*(str + 1)) || ft_isalpha(*(str + 1))
				|| *(str + 1) == '_'))
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
	char	*sub;
	char	*orig;
	char	*tmp;

	sub = NULL;
	orig = ft_calloc(sizeof(char), str_exp_count(mini, str) + 1);
	tmp = orig;
	while (*str)
	{
		if (*str == '$' && (ft_isalnum(*(str + 1)) || ft_isalpha(*(str + 1))
				|| *(str + 1) == '_'))
		{
			sub = ft_substr0(str + 1, count_exp(str + 1));
			if (ft_getenv(mini->en, sub))
			{
				ft_strlcpy(orig, ft_getenv(mini->en, sub),
					ft_strlen(ft_getenv(mini->en, sub)) + 1);
				orig += ft_strlen(ft_getenv(mini->en, sub));
			}
			str += ft_strlen(sub) + 1;
			free(sub);
		}
		else
			*(orig++) = *(str++);
	}
	*orig = '\0';
	return (tmp);
}
