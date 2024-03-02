/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 20:15:45 by mcamilli          #+#    #+#             */
/*   Updated: 2024/03/02 15:26:52 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

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
int ft_it_is_exp_valid(char *s)
{
	char *tmp;

	tmp = NULL;
	if (!(*s == '$' && (ft_isalnum(*(s+1)) || ft_isalpha(*(s+1)) || *(s+1) == '_')))
		return (0);
	tmp = ft_substr(s, 1, count_exp(s + 1));
	if (!getenv((const char *)tmp))
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

int str_exp_count(char *str)
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
			if (getenv((const char *)tmp))
				mem += ft_strlen(getenv((const char *)tmp));
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
			if (getenv((const char *)sub))
			{
				printf("166 orig + n = %s, pwd = %s, strlen %d\n",orig + n, getenv((const char *)sub), (int)ft_strlen(getenv((const char *)sub)));
				ft_strlcpy(orig + n, getenv((const char *)sub), ft_strlen(getenv((const char *)sub)));
				printf("168 orig + n = %s, pwd = %s, strlen %d\n",orig + n, getenv((const char *)sub), (int)ft_strlen(getenv((const char *)sub)));
				n += ft_strlen(getenv((const char *)sub)) - 1;
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

char *str_exp_realloc(char *str)
{
	char *sub;
	char *orig;
	char *tmp;

	sub = NULL;
	orig = malloc(sizeof(char) * str_exp_count(str) + 1);
	tmp = orig;
	while (*str)
	{
		if (*str == '$' && (ft_isalnum(*(str + 1)) || ft_isalpha(*(str + 1)) || *(str + 1) == '_'))
		{
			sub = ft_substr0(str + 1, count_exp(str + 1));
			if (getenv((const char *)sub))
			{
				ft_strlcpy(orig, getenv((const char *)sub), ft_strlen(getenv((const char *)sub)));
				orig += ft_strlen(getenv((const char *)sub)) -1;
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

int check_expan(char **c)
{
	int i;
	char *tmp;

	i = 0;
	tmp = NULL;
	while (c[i])
	{
		//printf("str = %s\n", c[i]);
		if (ft_strlen(c[i]) != (size_t)str_exp_count(c[i]) && c[i][0] != 39)
		{
			tmp = str_exp_realloc(c[i]);
			//c = str_exp_count(c[i]);
			printf("beforerealloc\n");
			swapStrings(&c[i], &tmp);
			free(tmp);
			printf("str = %s\n", c[i]);
			i++;
		}
		else
			i++;
	}
	printf("n righe %d\n", i);
	return (i);
}