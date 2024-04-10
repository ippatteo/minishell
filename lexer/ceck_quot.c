/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceck_quot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:16:16 by lpicciri          #+#    #+#             */
/*   Updated: 2024/04/05 01:47:07 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	realloc_quotes(t_mini *mini)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (mini->commands[i])
	{
		if (mini->commands[i][0] == D_QUOT || mini->commands[i][0] == QUOT)
		{
			tmp = ft_strdup(mini->commands[i]);
			free(mini->commands[i]);
			mini->commands[i] = ft_substr(tmp, 1, ft_strlen(tmp) - 2);
			free(tmp);
		}
		i++;
	}
}

char	*ft_getenv(char **en, char *s)
{
	int		i;
	char	*str;

	i = 0;
	while (en[i])
	{
		if (ft_strnstr(en[i], s, ft_strlen(s))
			&& !en[i][ft_exp_count_qutes(en[i])])
			return (" ");
		if (ft_strnstr(en[i], s, ft_strlen(s))
			&& en[i][ft_strlen(s)] == '=')
		{
			str = ft_strnstr(en[i], s, ft_strlen(s));
			return (str + ft_strlen(s) + 1);
		}
		else
			i++;
	}
	return (NULL);
}

int	c_error_quote(char *str, char c)
{
	int	mem;

	str++;
	mem = 1;
	while (*str && *str != c)
	{
		str++;
		mem++;
	}
	if (*str == '\0')
	{
		ft_putendl_fd("quote aperte col cazzo che lo gestisco\n", 2);
		g_exit = 127;
		return (0);
	}
	else
		return(++mem);
}

//questa va nel .h
int	no_open_quote(char *str)
{
	while (*str)
	{
		if(*str == D_QUOT || *str == QUOT)
		{
			if(!c_error_quote(str, *str))
				return(0);
			else
				str += c_error_quote(str, *str);
		}
		else
			str++;
	}
	return (1);
}


