/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 20:15:45 by mcamilli          #+#    #+#             */
/*   Updated: 2024/04/02 18:00:00 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	check_expan(t_mini *mini, char **c)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (c[i])
	{
		if (ft_strlen(c[i]) != (size_t)str_exp_count(mini, c[i])
			&& c[i][0] != 39)
		{
			tmp = str_exp_realloc(mini, c[i]);
			swap_strings(&c[i], &tmp);
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
		if (*str == '$' && *(str + 1) == '?')
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
		if (*str == '$' && *(str + 1) == '?')
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
			swap_strings(&c[i], &tmp);
			free(tmp);
			i++;
		}
		else
			i++;
	}
	return (i);
}
