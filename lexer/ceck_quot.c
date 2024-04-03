/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceck_quot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:16:16 by lpicciri          #+#    #+#             */
/*   Updated: 2024/04/03 17:48:34 by lpicciri         ###   ########.fr       */
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
