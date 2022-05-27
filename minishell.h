/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:44:50 by hejang            #+#    #+#             */
/*   Updated: 2022/05/27 14:08:31 by yukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>

# define TRUE 1
# define FALSE 0
# define ERROR -1

typedef struct s_lexer
{
	int		type;
	char	*value;
}			t_lexer;

enum type
{
	T_COMMAND = 1,
	T_WORD,
	T_FLAG,
	T_PIPE,
	T_REDIRECTION,
	D_QUOTE,
	S_QUOTE,
	T_NULL
}; 

enum quote_flag
{
	SINGLE_QUOTE = 1,
	DOUBLE_QUOTE
};

int		analyze_input(char *input);
char	**tokenize_input(char *input);

char	**ft_minishell_split(char const *str);
int		ft_wordcount(char const *str);
int		is_ifs(const char c);
int		is_redirection(const char *s);
int		is_quote(const char c);
#endif