/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:44:50 by hejang            #+#    #+#             */
/*   Updated: 2022/05/31 16:32:09 by hejang           ###   ########seoul.kr  */
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
	int				type;
	char			*value;
	// struct s_lexer	*plink;
}			t_lexer;

typedef struct s_data
{
	int				pipe_cnt;
	int				redirection_cnt;
	int				tokens_cnt;
	char			**tokens;  // tokens 배열 추가
	// t_lexer			*lexer; // 토큰배열을 구조체에 들고 다니면, lexer 구조체 말고 int *type을 들고 다녀도 괜찮을거 같은둣? 
	int				*type;
	struct s_ast	ast;
}			t_data;

typedef struct s_ast
{
	struct s_astnode	*prootnode;
}			t_ast;

typedef struct s_astnode
{
	int					visited;
	int					nodetype;
	t_lexer				*lexervalue;
	struct s_astnode	*pleftchild;
	struct s_astnode	*prightchild;
}			t_astnode;

typedef struct s_cmd
{
	char	*cmd[8];
}			t_cmd;

enum e_ast_node_type
{
	A_PIPE = 1,
	A_COMMAND,
	A_REDIRECTIONS,
	A_REDIRECTION,
	A_ARGUMENTS,
	A_ARGUMENT,
	A_FILEPATH,
	A_FILENAME
};

enum e_type
{
	T_COMMAND = 1,
	T_WORD,
	T_OPTION,
	T_PIPE,
	T_REDIRECTION,
	D_QUOTE,
	S_QUOTE,
	T_NULL
};

enum e_quote_flag
{
	SINGLE_QUOTE = 1,
	DOUBLE_QUOTE
};

//utils
void	*ft_calloc(size_t number, size_t size);
void	ft_free_all(char **ret);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);

int		analyze_input(char *input);

// tokens
char	**tokenize_input(t_data *data, char *input);
char	**ft_minishell_split(const char *str);
int		ft_wordcount(char const *str);
int		is_ifs(const char c);
int		is_redirection(const char *s);
int		is_quote(const char c);
int		is_pipe(const char *s);
//lexer
void	lexical_analysis(t_data *data);
t_cmd	*create_cmd_struct(void);
int		is_cmd(char *value);
int		is_option(char *value);
//parser
void	syntax_analysis(t_data *data);

#endif
