/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 19:01:08 by hejang            #+#    #+#             */
/*   Updated: 2022/06/26 13:49:30 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/*
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <signal.h>
# include <fcntl.h>
*/
# include "limits.h"
# include <stdlib.h>
# include "minishell_define.h"

void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t number, size_t size);
char		*ft_free_all(char **ret);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);
int			ft_split_str(char *str, char **tokens);
int			ft_wordlen(char const *str);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strchr(const char *s, int c);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		**ft_split(char const *s, char c);
long long	ft_atoi(const char *str, t_astnode *args_node);
char		*ft_itoa(size_t num);
t_envv_node	*ft_lstnew(t_envv_node element);
void		ft_lstadd_back(t_envv_node *new);
void		remove_ll_element(t_envv_node **p_list, char *key);


//is_?
int		is_ifs(const char c);
int		is_redirection(const char *s);
int		is_quote(const char c);
int		is_pipe(const char *s);
int		is_option(char *value);
int		is_valid_env(char *str);
int		is_env(char *value);
int		ft_is_alpha(char c);
int		ft_is_digit(int c);

int		case_redirection(char const *str, int *i);

char	*remove_quote(char *quote_str);

void	ft_error_message(char *message, int exit_status);

//data

// void	init_data(void);
void	free_data_lexer(void);
void	reset_data(void);
void	free_data(void);
#endif
