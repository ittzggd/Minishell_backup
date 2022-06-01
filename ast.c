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
		if (type[index] == T_PIPE) // index = 4
		{
			ast_node->nodetype = A_PIPE; // astnode = rootNode => 루트 노드는 파이프

			// lnode = insertPLeftChild(ast_node, A_COMMAND);
			// rnode = insertPRightChild(ast_node, 0);
			ast_node->pleftchild = insert_leftchildnode_ast(ast_node, A_COMMAND);
			// tree_cmd(ast_node->left, index, data); => index 값 의논 필요
			ast_node->prightchild = insert_rightchildnode_ast(ast_node, 0);
			// if (recur_pipe(rnode, index + 1, data))
			if (recur_pipe(ast_node->prightchild, index + 1, data))
				return(TRUE);
		}
		index++;
	}
//	if (tokens[index] == NULL) // 일단 주석
		ast_node->node_type = A_COMMAND;
		// tree_cmd(ast_node, index, data); => index 의논 필요
	return (TRUE);
}

// cmd 함수의 역할은 첫번째 리다이렉션을 만날때까지 탐색해서
// args   reds  트리 노드를 만드는 것이다
void	tree_cmd(t_astnode *ast_node, int index, t_data data)
{
	char	**tokens;
	int		*type;
	// t_astnode	*lnode;
	// t_astnode	*rnode;
	if (astnode->nodetype != A_COMMAND)
		return ;
	tokens = data->plexer->pptokens;
	type = data->plexer->type;
	// lnode = insertPLeftChild(ast_node, A_ARGUMENTS);  // 
	// rnode = insertPRightChild(ast_node, 0);
	ast_node->pleftchild = insert_leftchildnode_ast(ast_node, A_ARGUMENTS);
	ast_node->prightchild = insert_rightchildnode_ast(ast_node, 0);
	// tree_args 함수 호출
	tree_args(ast_node->pleftchild, index, data);
	// while(type[index]tokens[index])
	while (type[index] != T_PIPE && tokens[index])
	{
		if (type[index] = T_REDIRECTION)
		{
			ast_node->prightchild->nodetype = A_REDIRECTIONS;
			// tree_reds 함수 호출
			tree_reds(ast_nnode->prightchild, index, data);
			break ;
		}
		index++;
	}
}


// args 밑부분 만들기
void	tree_args(t_astnode *ast_node, int index, t_data data)
{
	char	**tokens;
	int		*type;

	if (astnode->nodetype != A_ARGUMENTS)
		return ;
	tokens = data->plexer->pptokens;
	type = data->plexer->type;
	ast_node->pleftchild = insert_leftchildnode_ast(ast_node, A_FILEPATH);
	ast_node->prightchild = insert_rightchildnode_ast(ast_node, A_ARGUMENT);
	while (type[index] != T_REDIRECTION && tokens[index])
	{
		// A_FILEPATH와 A_ARGUMENT value 넣기
		index++;
	}
}
// reds 밑부분 만들기
void	tree_reds(t_astnode *ast_node, int index, t_data data)
{
	char	**tokens;
	int		*type;

	if (astnode->nodetype != A_REDIRECTIONS)
		return ;
	tokens = data->plexer->pptokens;
	type = data->plexer->type;
	ast_node->pleftchild = insert_leftchildnode_ast(ast_node, A_REDIRECTION);
	ast_node->prightchild = insert_rightchildnode_ast(ast_node, 0);
	if (type[index] == T_REDIRECTION)
	{
		ast_node->pleftchild-> pleftchild = insert_leftchildnode_ast(ast_node, A_REDIRECTION_TYPE);
		ast_node->pleftchild->prightchild = insert_rightchildnode_ast(ast_node, A_FILENAME);
		//A_REDIRECTION_TYPE 와 A_FILENAME 노드에 value 넣기 추가해야 함
	}
	index++; 
	while (type[index] != T_PIPE && tokens[index])
	{
		if (type[index] == T_REDIRECTION)
		{
			ast_node->prightchild->nodetype = A_REDIRECTIONS;
			tree_reds(ast_node->prightchild, index, data);
			break ;
		}
		index++;
	}
}