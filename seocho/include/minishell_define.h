/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_define.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 19:03:00 by yukim             #+#    #+#             */
/*   Updated: 2022/06/26 19:32:11 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_DEFINE_H
# define MINISHELL_DEFINE_H

# include <termios.h>

# define TRUE 1
# define FALSE 0
# define ERROR -1
# define END -1
# define ALLOCATE_FAILED -2


typedef struct s_astnode
{
	int					visited;
	int					nodetype;
	int					*pvalue_index; // 마지막 인덱스에 -1 저장
	struct s_astnode	*pleftchild;
	struct s_astnode	*prightchild;
}			t_astnode;

typedef struct s_ast
{
	struct s_astnode	*prootnode;
}			t_ast;


typedef struct s_lexer
{
	char	**pptokens;
	int		*ptype;
}			t_lexer;

typedef struct s_data
{
	int						std_fd[2];
	int						heredoc_fd[2];
	struct termios			origin_term;
	struct termios			changed_term;
	struct s_envv_node		*envv_list;
	int						envv_cnt;
	int						exit_status;
	int						tokens_cnt;
	int						redirection_cnt;
	int						pipe_cnt;
	struct s_lexer			lexer;
	struct s_ast			ast;
	int						p_flag;
	int						heredoc_flag;
}			t_data;


typedef struct s_envv_node
{
	char				*key;
	char				*value;
	int					init_flag;
	struct s_envv_node	*p_link;
}			t_envv_node;


typedef struct s_cmd
{
	char	*cmd[9];
}			t_cmd;

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
