/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 19:01:08 by hejang            #+#    #+#             */
/*   Updated: 2022/05/31 22:09:12 by yukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/*
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
*/

void	*ft_calloc(size_t number, size_t size);
void	ft_free_all(char **ret);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
int		ft_split_str(char *str, char **ret);
int		ft_wordlen(char const *str);

//is_?
int		is_ifs(const char c);
int		is_redirection(const char *s);
int		is_quote(const char c);
int		is_pipe(const char *s);
int		is_cmd(char *value);
int		is_option(char *value);



#endif