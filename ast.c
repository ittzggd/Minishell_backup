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
*/
int	recur_pipe(t_astnode *ast_node, int index, t_data data) // 가장 처음은 초기화된 rootNode, index = 0 이 들어옴
{
	char **tokens;
	int *type;
	// t_astnode	*lnode; 	=> ast_node 구조체의 pleftchild, prightchild 사용
	// t_astnode	*rnode;

	tokens = data->plexer->pptokens;
	type = data->plexer->ptype;
	/*
	ast_node->plexer // ?????? ast_node는 ft_calloc으로 만들어짐. data->plexer와 연결 필요
	*/
	while(tokens[index])
	{
		// echo "hi" > a.txt | cat
		if (type[index] == T_PIPE) // index = 5
		{
			ast_node->nodetype = A_PIPE; // astnode = rootNode => 루트 노드는 파이프

			// lnode = insertPLeftChild(ast_node, A_COMMAND);
			// rnode = insertPRightChild(ast_node, 0);
			ast_node->pleftchild = insert_leftchildnode_ast(ast_node, A_COMMAND);
			ast_node->prightchild = insert_rightchildnode_ast(ast_node, 0);
			// if (recur_pipe(rnode, index + 1, data))
			if (recur_pipe(ast_node->prightchild, index + 1, data))
				return(TRUE);
		}
		index++;
	}
//	if (tokens[index] == NULL) // 일단 주석
		ast_node->node_type = A_COMMAND;
	return (TRUE);
}
/*
	// cmd 함수의 역할은 첫번째 리다이렉션을 만날때까지 탐색해서
	// args   reds  트리 노드를 만드는 것이다
	void	tree_cmd(t_astnode *ast_node, int index, t_data data)
	{
		char	**tokens;
		char	*type;
		// t_astnode	*lnode;
		// t_astnode	*rnode;

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
