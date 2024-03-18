/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcamilli <mcamilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:08:42 by lpicciri          #+#    #+#             */
/*   Updated: 2024/03/15 17:23:26 by mcamilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

void				ft_bzero(void *str, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int nb, int fd);
void				*ft_memset(void *str, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *str, int c, size_t n);
void				*ft_calloc(size_t num, size_t dim);
int					ft_memcmp(const void *str1, const void *str2, size_t n);
int					ft_isalpha(int n);
int					ft_isdigit(int n);
int					ft_isalnum(int n);
int					ft_isascii(int n);
int					ft_isprint(int n);
int					ft_toupper(int ch);
int					ft_tolower(int ch);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
int					ft_atoi(const char *str);
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
char				*ft_strchr(const char *str, int c);
char				*ft_strrchr(const char *str, int c);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strdup(const char *str);
char				*ft_substr(char const *str, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				**ft_split(char const *s, char c);
void				ft_striteri(char *s, void (*f)(unsigned int, char*));
int					ft_putstr(char *s);


#endif
