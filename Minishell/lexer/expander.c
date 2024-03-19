/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 20:15:45 by mcamilli          #+#    #+#             */
/*   Updated: 2024/03/19 14:50:52 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"



char *ft_getenv(char **en, char *s)
{
	int i;

	i = 0;
	char *str;
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
//conta dall'expander quanti caratteri ci sono, serve al substr
//ma deve esser fatto partire da dopo il $

int	count_exp(char *str)
{
	int mem;

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

// e sia un controllo che capisce se e da
//saltare sia un contrololo che ritorna quanto sia da sltare
int ft_it_is_exp_valid(t_mini *mini, char *s)
{
	char *tmp;

	tmp = NULL;
	if (*s == '$' && *(s+1) == '?')
		return (0);
	if (!(*s == '$' && (ft_isalnum(*(s+1)) || ft_isalpha(*(s+1)) || *(s+1) == '_')))
		return (0);
	tmp = ft_substr(s, 1, count_exp(s + 1));
	if (!ft_getenv(mini->en, tmp))
	{
		free(tmp);
		return(count_exp(s + 1) + 1);
	}
	else
	{
		free(tmp);
		return (0);
	}
}
//conta in una stringa quanta memoria va riallocata per
//l'expander

int str_exp_count(t_mini *mini, char *str)
{
	char *tmp;
	int mem;

	tmp = NULL;
	mem = 0;
	while (*str)
	{
		if (*str == '$' && (ft_isalnum(*(str + 1)) || ft_isalpha(*(str + 1)) || *(str + 1) == '_')) //deve rimanere cosi
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





/*
char *str_exp_realloc(char *str)
{
	char *tmp;
	char *sub;
	char *orig;
	int i;
	int n;

	sub = NULL;
	tmp = NULL;
	n = 0;
	i = 0;
	orig = ft_calloc(sizeof(char), str_exp_count(str) + 1);
	while (str[i])
	{
		//printf("i = %d, str = %c\n", i, str[i]);
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) || ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
		{
			//printf("attivato $\n");
			i++;
			sub = ft_substr0(str + i, count_exp(str + i));
				printf("sub = %s\n", sub);
			if (ft_getenv(mini, sub))
			{
				printf("166 orig + n = %s, pwd = %s, strlen %d\n",orig + n, ft_getenv(mini, sub), (int)ft_strlen(ft_getenv(mini, sub)));
				ft_strlcpy(orig + n, ft_getenv(mini, sub), ft_strlen(ft_getenv(mini, sub)));
				printf("168 orig + n = %s, pwd = %s, strlen %d\n",orig + n, ft_getenv(mini, sub), (int)ft_strlen(ft_getenv(mini, sub)));
				n += ft_strlen(ft_getenv(mini, sub)) - 1;
			}
			i += ft_strlen(sub);
			free(sub);
		}
		else
		{
			printf("168 str = %d, orig = %d\n", str[i], orig[n]);
			orig[n] = str[i];
			n++;
			i++;
		}
	}
	orig[n] = '\0';
	return (orig);
}

questa funziona cancellare dopo
*/

char *str_exp_realloc(t_mini *mini, char *str)
{
	char *sub;
	char *orig;
	char *tmp;

	sub = NULL;
	orig = ft_calloc(sizeof(char), str_exp_count(mini, str) + 1);
	tmp = orig;
	while (*str)
	{
		if (*str == '$' && (ft_isalnum(*(str + 1)) || ft_isalpha(*(str + 1)) || *(str + 1) == '_'))
		{
			sub = ft_substr0(str + 1, count_exp(str + 1));
			if (ft_getenv(mini->en, sub))
			{
				ft_strlcpy(orig, ft_getenv(mini->en, sub), ft_strlen(ft_getenv(mini->en, sub)));
				orig += ft_strlen(ft_getenv(mini->en, sub)) -1;
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

int check_expan(t_mini *mini, char **c)
{
	int i;
	char *tmp;

	i = 0;
	tmp = NULL;
	while (c[i])
	{

		if (ft_strlen(c[i]) != (size_t)str_exp_count(mini, c[i]) && c[i][0] != 39)
		{
			tmp = str_exp_realloc(mini, c[i]);
			swapStrings(&c[i], &tmp);
			free(tmp);
			i++;
		}
		else
			i++;
	}
	return (i);
}



int str_exp_count_2(t_mini *mini, char *str, char *sub)
{
	int mem;

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

char *str_exp_realloc_2(t_mini *mini, char *str)
{
	char *sub;
	char *orig;
	char *tmp;

	sub = ft_itoa(g_exit);
	//printf("sub = %s count = %d ", sub, str_exp_count_2(mini, str, sub));
	orig = ft_calloc(sizeof(char), str_exp_count_2(mini, str, sub) + 1);
	tmp = orig;
	while (*str)
	{
		if (*str == '$' && *(str + 1) == '?')
		{
			ft_strlcpy(orig, sub, 8);
			printf("ft_strlcpy = %d\n", (int)ft_strlcpy(orig, sub, 8));
			printf("ft_strlcpy = %s\n", orig);
			orig += ft_strlen(sub);
			str += 2;
		}
		else
			*(orig++) = *(str++);
	}
	free(sub);
	*orig = '\0';
	printf("porcoddio = %s\n", tmp);
	return (tmp);
}

int check_expan_2(t_mini *mini, char **c)
{
	int i;
	char *tmp;

	i = 0;
	tmp = NULL;
	while (c[i])
	{
		if (ft_strnstr(c[i], "$?", ft_strlen(c[i])))
		{
			tmp = str_exp_realloc_2(mini, c[i]);
			swapStrings(&c[i], &tmp);
			free(tmp);
			i++;
		}
		else
			i++;
	}
	return (i);
}