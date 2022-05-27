/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:44:50 by hejang            #+#    #+#             */
/*   Updated: 2022/05/27 19:57:31 by yukim            ###   ########.fr       */
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
	t_lexer	*plink;
}			t_lexer;

typedef struct s_cmd
{
	char *cmd[]
}			t_cmd;

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

//utils
void	*ft_calloc(size_t number, size_t size);
void	ft_free_all(char **ret);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);

int		analyze_input(char *input);
// tokens
char	**tokenize_input(char *input);
char	**ft_minishell_split(const char *str);
int		ft_wordcount(char const *str);
int		is_ifs(const char c);
int		is_redirection(const char *s);
int		is_quote(const char c);
int		is_pipe(const char *s);
//lexer
t_lexer	*lexical_analysis(char **tokens);
//parser

#endif