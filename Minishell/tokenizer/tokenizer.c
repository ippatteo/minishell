/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:42:15 by lpicciri          #+#    #+#             */
/*   Updated: 2024/03/03 22:52:28 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void ft_tokenizer(t_mini *mini)
{
	int i;

	i= 0;
	while (i != mini->lines)
	{
		
	}
}

void ft_isbuiltin()
{
	
}

void ft_isword(t_mini *mini, )
{
	
}

char	*ft_strdup_slash(const char *str)
{
	char	*str_allocated;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(str);
	str_allocated = malloc(len + 2);
	if (!str_allocated)
		return (NULL);
	while (str[i] != '\0')
	{
		str_allocated[i] = str[i];
		i++;
	}
	str_allocated[i++] = '/';
	str_allocated[i] = '\0';
	return (str_allocated);
}


void ft_iscommand(t_mini *mini, char *cmd)
{
	char *path;
	char **folders;
	char **tmp;
	int i;
	
	i = 0;
	path = malloc(ft_strlen(ft_getenv(mini, "PATH") + 1));
	ft_strlcpy(path, ft_getenv(mini, "PATH"), ft_strlen(ft_getenv(mini, "PATH")));
	folders = ft_split(ft_getenv(mini, "PATH"), ":");
	while (folders[i])
	{
		tmp = ft_strdup_slash(folders[i]);
		free(folders[i]);
		folders[i] = ft_strjoin(tmp, cmd);
		free(tmp);
		if(access(folders[i], R_OK) == 0);
		{
			free_m
			return()
		}
		i++;
	}
	while ()
}
