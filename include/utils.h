/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 19:01:08 by hejang            #+#    #+#             */
/*   Updated: 2022/06/01 17:02:59 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/*
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>

# include <signal.h>
# include <fcntl.h>
*/
# include <stdlib.h>

void	*ft_calloc(size_t number, size_t size);
void	ft_free_all(char **ret);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
int		ft_split_str(char *str, char **ret);
int		ft_wordlen(char const *str);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
//is_?
int		is_ifs(const char c);
int		is_redirection(const char *s);
int		is_quote(const char c);
int		is_pipe(const char *s);
int		is_cmd(char *value);
int		is_option(char *value);



#endif