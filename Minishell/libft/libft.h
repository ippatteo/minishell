/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 03:00:55 by mcamilli          #+#    #+#             */
/*   Updated: 2023/09/14 16:50:45 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <string.h>
# include <ctype.h>
# include <unistd.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_isalpha(int c);
int		ft_tolower(int c);
int		ft_isdigit(int c);
int		ft_toupper(int c);
int		ft_isalnum(int c);
char	*ft_strchr(const char *str1, int ch);
int		ft_isascii(int c);
int		ft_isprint(int c);
char	*ft_strrchr(const char *str1, int ch);
size_t	ft_strlen(const	char *s);
void	*ft_memset(void *b, int c, size_t n);
void	*ft_memchr(const void	*str1, int c, size_t ch);
void	ft_bzero(void *t, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memcpy(void *dst, const void *srv, size_t n);
size_t	ft_strlcpy(char *dest, const char *source, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strnstr(const char *hk, const char *nd, size_t len);
int		ft_atoi(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s, char *b);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
int		ft_putstr(char	*s);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
char	*risultato(char *s);
char	*ft_read_file(int fd, char *stash);
char	*next(char *s);
char	*get_next_file(int fd);
void	ft_putstr_fd(char *s, int fd);
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);

#endif
