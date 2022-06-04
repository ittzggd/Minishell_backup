/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_define.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim<yukim@student.42seoul.kr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 19:03:00 by yukim             #+#    #+#             */
/*   Updated: 2022/05/31 19:03:39 by yukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H

# define TRUE 1
# define FALSE 0
# define ERROR -1

typedef struct s_lexer
{
	char	**pptokens;
	int		*ptype;
}			t_lexer;

typedef struct s_data
{
	int						pipe_cnt;
	int						redirection_cnt;
	int						tokens_cnt;
	t_lexer					*plexer;
	struct s_ast			*p_ast;
	struct s_ioredirection	**io_red;
}			t_data;

typedef struct s_ast
{
	struct s_astnode	*prootnode;
}			t_ast;

typedef struct s_astnode
{
	int					visited;
	int					nodetype;
	int					*pvalue_index;
	struct s_astnode	*pleftchild;
	struct s_astnode	*prightchild;
}			t_astnode;

typedef struct s_cmd
{
	char	*cmd[8];
}			t_cmd;

typedef	struct s_ioredirection
{
	char	*red_stdin;
	char	*red_stdout;
	//char	*heredoc;
}			t_ioredirection;


enum e_ast_node_type
{
	// 트리그림 이름이랑 똑같이 바꾸기
	A_PIPE = 1,
	A_COMMAND,
	A_REDIRECTIONS,
	A_REDIRECTION,
	A_REDIRECTION_TYPE,
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
	T_NULL,
	T_ENV
};

enum e_quote_flag
{
	SINGLE_QUOTE = 1,
	DOUBLE_QUOTE
};

enum e_io_redirection
{
	STDINPUT = 1,
	STDOUTPUT,
	HEREDOC
};

#endif
