/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:20:15 by hejang            #+#    #+#             */
/*   Updated: 2022/05/31 22:08:53 by yukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"
#include "./include/minishell_define.h"
#include "./include/utils.h"

// cmd는 분리해서 생각하기
// 이제 남은 일 cmd안에서 red
// pipe함수랑 구조 비슷할 듯

/*
			  pipe
		cmd			pipe
				cmd		cmd

	int	recur_pipe(t_astnode *ast_node, int index, t_data data)
	{
		char **tokens;
		char *type;
		t_astnode	*lnode;
		t_astnode	*rnode;

		tokens = data->plexer->pptokens;
		type = data->plexer->ptype;
		while(tokens[index])
		{
			if(type[index] == T_PIPE)
			{
				ast_node->nodetype = T_PIPE; // 노드 타입을 따로 만들어야 될까?
				lnode = insertPLeftChild(ast_node, A_COMMAND);  // 
				rnode = insertPRightChild(ast_node, 0);
				if(recur_pipe(rnode, index, data))
					return(TRUE);
			}
			index++;
		}
	//	if(tokens[index] == NULL) // 일단 주석
			ast_node->node_type = A_COMMAND;
		return (TRUE)
	}

	// cmd 함수의 역할은 첫번째 리다이렉션을 만날때까지 탐색해서
	// args   reds  트리 노드를 만드는 것이다
	void	tree_cmd(t_astnode *ast_node, int index, t_data data)
	{
		char **tokens;
		char	*type;
		t_astnode	*lnode;
		t_astnode	*rnode;

		if (astnode->nodetype != A_COMMAND)
			return ;
		tokens = data->plexer->pptokens;
		lnode = insertPLeftChild(ast_node, A_ARGUMENTS);  // 
		rnode = insertPRightChild(ast_node, 0);
		while(type[index]tokens[index])
		{
			if(type[index] = T_REDIRECTION)
			{
				rnode->nodetype = A_REDIRECTIONS;
			}
			index++;
		}
	}
*/

// args 밑부분 만들기
// reds 밑부분 만들기
