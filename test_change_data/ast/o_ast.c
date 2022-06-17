/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_ast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:20:15 by hejang            #+#    #+#             */
/*   Updated: 2022/06/15 20:22:32 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//1. 맨 처음 root node랑 ast 구조체 할당해주는 부분 못 찾아서 추가
//2. tree_reds 는 void return 해서 ERROR 리턴 못 함


#include "../include/minishell.h"
#include "../include/tree_utils.h"

// strdup 과 strjoin 가져오기
// ast완성 후, pptokes , ptype , plexer free?!?!

/*
			  pipe
		cmd			pipe
				cmd		cmd
*/

void	init_ast(void)
{
	t_ast		*ast;
	t_astnode	*root_node;

	// if(data)
	// {
		ast = malloc(sizeof(t_ast));
		if(!ast)
			return ;
		root_node = ft_calloc(1, sizeof(t_astnode));
		if(!root_node)
		{
			free(ast);
			return ;
		}
		data.p_ast = ast;
		data.p_ast->prootnode = root_node;
	// }
	recur_pipe(root_node, 0);
}

int	recur_pipe(t_astnode *ast_node, int index) // 가장 처음은 초기화된 rootNode, index = 0 이 들어옴
{
	char **tokens;
	int *type;
	int c_index;

	tokens = data.plexer->pptokens;
	type = data.plexer->ptype;
	c_index = index;
	while(tokens[index])
	{
		if (type[index] == T_PIPE)
		{
			ast_node->nodetype = A_PIPE;
			if(init_idx(index, ast_node) == ERROR)  //파이프 동가리 인덱스 저장
				return (ERROR);
			ast_node->pleftchild = insert_leftchildnode_ast(ast_node, A_COMMAND);
			tree_cmd(ast_node->pleftchild, c_index);
			ast_node->prightchild = insert_rightchildnode_ast(ast_node, 0);
			if (recur_pipe(ast_node->prightchild, index + 1))
				return (TRUE);
		}
		index++;
	}
//	if (tokens[index] == NULL) // 일단 주석
		ast_node->nodetype = A_COMMAND;
		tree_cmd(ast_node, c_index);
	return (TRUE);
}

void	tree_cmd(t_astnode *ast_node, int index)
{
	char	**tokens;
	int		*type;
	int		c_index;

	if (ast_node->nodetype != A_COMMAND)
		return ;
	tokens = data.plexer->pptokens;
	type = data.plexer->ptype;
	ast_node->pleftchild = insert_leftchildnode_ast(ast_node, 0);
	ast_node->prightchild = insert_rightchildnode_ast(ast_node, A_ARGUMENTS);
	tree_args(ast_node->prightchild, index);
	while (type[index] != T_PIPE && tokens[index])
	{
		if (type[index] == T_REDIRECTION)
		{
			ast_node->pleftchild->nodetype = A_REDIRECTIONS;
			tree_reds(ast_node->pleftchild, index);
			break ;
		}
		index++;
	}
}

// cmd 함수의 역할은 첫번째 리다이렉션을 만날때까지 탐색해서
// args   reds  트리 노드를 만드는 것이다
// void	tree_cmd(t_astnode *ast_node, int index)
// {
// 	char	**tokens;
// 	int		*type;

// 	if (ast_node->nodetype != A_COMMAND)
// 	 	return ;
// 	tokens = data.plexer->pptokens;
// 	type = data.plexer->ptype;
// 	ast_node->pleftchild = insert_leftchildnode_ast(ast_node, 0);
// 	// ast_node->prightchild = insert_rightchildnode_ast(ast_node, A_ARGUMENTS);
// 	ast_node->prightchild = insert_rightchildnode_ast(ast_node, 0);
// 	if (type[index] == T_COMMAND) // == Command
// 	{
// 		ast_node->prightchild->nodetype = A_ARGUMENTS;
// 		tree_args(ast_node->prightchild, index);
// 	}
// 	while (type[index] != T_PIPE && tokens[index])
// 	{
// 		if (type[index] == T_REDIRECTION)
// 		{
// 			ast_node->pleftchild->nodetype = A_REDIRECTIONS;
// 			tree_red
// 			s(ast_node->pleftchild, index); // red와 red다음 애만 추가되도록
// 			break ;
// 		}
// 		index++;
// 	}
// }


// args 밑부분 만들기
int	tree_args(t_astnode *ast_node, int index)
{
	char		*tmp;
	char		**tokens;
	int			*type;
	t_astnode	*args_leftchild;
	t_astnode	*args_rightchild;

	if (ast_node->nodetype != A_ARGUMENTS)
		return (ERROR);
	tokens = data.plexer->pptokens;
	type = data.plexer->ptype;
	args_leftchild = ast_node->pleftchild;
	args_rightchild = ast_node->prightchild;
	args_leftchild = insert_leftchildnode_ast(ast_node, A_FILEPATH);
	while(tokens[index] && type[index] != T_PIPE)
	{
		if (type[index] == T_COMMAND)
			break;
		index++;
	}
	if(init_idx(index, args_leftchild) == ERROR)
		return (ERROR);
	args_rightchild = insert_rightchildnode_ast(ast_node, A_ARGUMENT);
	while (tokens[index] && type[index] != T_PIPE)
	{
		if (type[index] == T_REDIRECTION) // red filename
			index++;
		else if(init_idx(index, args_rightchild) == ERROR)
				return (ERROR);
		index++;
	}
	return (TRUE);
}
// reds 밑부분 만들기
void	tree_reds(t_astnode *ast_node, int index)
{
	char		**tokens;
	int			*type;
	t_astnode	*reds_leftchild;
	t_astnode	*reds_rightchild;
	
	if (ast_node->nodetype != A_REDIRECTIONS)
		return ;
	tokens = data.plexer->pptokens;
	type = data.plexer->ptype;
	reds_leftchild = insert_leftchildnode_ast(ast_node, A_REDIRECTION); // RED
	reds_rightchild = insert_rightchildnode_ast(ast_node, 0); // REDS
	if (type[index] == T_REDIRECTION)
	{
		// RED->leftchild, RED->Rightchild
		reds_leftchild->pleftchild = insert_leftchildnode_ast(reds_leftchild, A_REDIRECTION_TYPE);
		reds_leftchild->prightchild = insert_rightchildnode_ast(reds_leftchild, A_FILENAME);
		if(init_idx(index, reds_leftchild->pleftchild) == ERROR)
			return ;
		if(init_idx(index + 1, reds_leftchild->prightchild) == ERROR)
			return ;
	}
	index++;
	while (type[index] != T_PIPE && tokens[index])
	{
		if (type[index] == T_REDIRECTION)
		{
			reds_rightchild->nodetype = A_REDIRECTIONS;
			tree_reds(reds_rightchild, index);
			return ;
		}
		index++;
	}
}

void	delete_ast(t_astnode *node)
{
	if(node)
	{
		delete_ast(node->pleftchild);
		delete_ast(node->prightchild);
		free(node);
		node = NULL;
	}
}

void free_ast(t_ast *ast)
{
	if(ast)
	{
		delete_ast(ast->prootnode);
		free(ast);
		ast = NULL;
	}
}
