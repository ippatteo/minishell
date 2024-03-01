/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 20:15:45 by mcamilli          #+#    #+#             */
/*   Updated: 2024/03/01 03:10:17 by mcamilli         ###   ########.fr       */
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
	printf("count exp: mem = %d str = %s\n", mem, str - mem);
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
	char *debug;

	tmp = NULL;
	mem = 0;
	debug = ft_strdup(str);
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
	printf("str exp count 86: mem = %d str = %s\n", mem, debug);
	free(debug);
	return (mem);
}

size_t	ft_strlcpy2(char *dest, const char *source, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(source);
	if (n > 0)
	{
		while (source[i] && i < (n - 1))
		{
			dest[i] = source[i];
			i++;
		}
		//dest[i] = '\0';
	}
	return (j);
}
//void str_exp_realloc_init(char *tmp)
//rialloca la memoria e riempe la stringa levando
//$abcde e mettendo getenv se esiste
char	*ft_substr0(char *s, int len)
{
	char	*s2;

	if (!s)
		return (NULL);
	s2 = (char *)ft_calloc(len + 1, sizeof(char));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, (s), len + 1);
	return (s2);
}

void swapStrings(char **str1, char **str2)
{
	char *temp = *str1;

	*str1 = *str2;
	*str2 = temp;
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
		if (ft_strlen(c[i]) != str_exp_count(c[i]) && c[i][0] != 39)
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

//conta quanti caratteri contengono le virgolette, virgolette comprese
int	count_mem_quote(char *str, char c)
{
	int	mem;

	mem = 1;
	str++;
	while(*str && *str != c)
	{
		//if(ft_it_is_exp_valid(str) && c == '"')
		//	str += ft_it_is_exp_valid(str);
		//else
		//{
			mem++;
			str++;
		//}
	}
	if (*str == '\0')
		return(0);
	mem++;
	return (mem);
}
//conta quansiasi cosa non sia una parola, virgolette, pipe e redirection
int count_quot_pipe_redir(char *str, char c)
{
	if (c == '<' || c =='>')
	{
		++str;
		if (*str == c)
			return (2);
		else
			return (1);
	}
	else if (c == '|')
	{
		++str;
		return (1);
	}
	else if ((*str == 34) || (*str == 39))
		return (count_mem_quote(str, c));
	else
		return (0);
}
//conta quanti char ci sono in una parola "normale"
int	count_words(char *str)
{
	int mem;

	mem = 0;
	while (*str)
	{
		if ((*str == '>') || (*str == '<')
			|| (*str == '|') || (*str == 34) || (*str == 39) || (*str == ' '))
				break ;
		else
		{
			str++;
			mem++;
		}
	}
	return (mem);
}

//conta quanta memoria bisogna allocare aggiungendo il +1 del \0 ogni colta
//restituisce 0 in caso di syntax error
size_t	count_mem(char *s)
{
	int mem;

	mem = 0;
	while (*s)
	{
		if ((*s == '>') || (*s == '<')
			|| (*s == '|') || (*s == 34) || (*s == 39))
		{
			mem += count_quot_pipe_redir(s, *s) + 1;
			if (!count_quot_pipe_redir(s, *s))
				return (-1);
			s += count_quot_pipe_redir(s, *s);
		}
		else if (*s == ' ' || *s == '	' )
			s++;
		else if (ft_it_is_exp_valid(s))
			s += ft_it_is_exp_valid(s);
		else
		{
			mem += count_words(s) + 1;
			s += count_words(s);
		}
	}
	return (mem);
}

//una volta allocata la memoria giusta riempe la matrice
size_t	split_mem(char *s, char **str)
{
	int i;

	i = 0;
	while (*s)
	{
		if ((*s == '>') || (*s == '<')
			|| (*s == '|') || (*s == 34) || (*s == 39))
		{
			str[i] = ft_substr(s, 0, count_quot_pipe_redir(s, *s));
			s += count_quot_pipe_redir(s, *s);
			i++;
		}
		else if (*s == ' ' || *s == '	')
			s++;
		else if (ft_it_is_exp_valid(s))
			s += ft_it_is_exp_valid(s);
		else
		{
			str[i] = ft_substr(s, 0, count_words(s));
			s += count_words(s);
			i++;
		}
	}
	str[i] = 0;
	return (i);
}

