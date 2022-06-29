/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_ast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:20:15 by hejang            #+#    #+#             */
/*   Updated: 2022/06/30 06:11:52 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//1. 맨 처음 root node랑 ast 구조체 할당해주는 부분 못 찾아서 추가
//2. tree_reds 는 void return 해서 ERROR 리턴 못 함


#include "../include/minishell.h"

int	insert_redschild(t_astnode *reds_leftchild, t_astnode *reds_rightchild, int index);
int	args_utils(int *index, t_astnode *args_rightchild);

void	init_ast(void)
{
	t_astnode	*root_node;

	calloc_nullcheck(&root_node, 1, sizeof(t_astnode));
	data.ast.prootnode = root_node;
	recur_pipe(root_node, 0);
}

int	recur_pipe(t_astnode *ast_node, int index) // 가장 처음은 초기화된 rootNode, index = 0 이 들어옴
{
	char **tokens;
	int c_index;

	tokens = data.lexer.pptokens;
	c_index = index;
	while(tokens[index])
	{
		if (data.lexer.ptype[index] == T_PIPE)
		{
			ast_node->nodetype = A_PIPE;
			init_idx(index, ast_node);
			ast_node->pleftchild = insert_leftchildnode_ast(ast_node, A_COMMAND);
			tree_cmd(ast_node->pleftchild, c_index);
			ast_node->prightchild = insert_rightchildnode_ast(ast_node, 0);
			if (recur_pipe(ast_node->prightchild, index + 1))
				return (TRUE);
		}
		index++;
	}
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
	tokens = data.lexer.pptokens;
	type = data.lexer.ptype;
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

int	insert_redschild(t_astnode *reds_leftchild, t_astnode *reds_rightchild, int index)
{
	t_astnode	*leftchild;
	t_astnode	*rightchild;

	leftchild = reds_leftchild->pleftchild;
	rightchild = reds_leftchild->prightchild;
	leftchild = insert_leftchildnode_ast(reds_leftchild, A_REDIRECTION_TYPE);
	rightchild = insert_rightchildnode_ast(reds_leftchild, A_FILENAME);
	init_idx(index, reds_leftchild->pleftchild);
	init_idx(index + 1, reds_leftchild->prightchild);
	return (TRUE);
}

// args 밑부분 만들기
int	tree_args(t_astnode *ast_node, int index)
{
	t_astnode	*args_leftchild;
	t_astnode	*args_rightchild;

	if (ast_node->nodetype != A_ARGUMENTS)
		return (ERROR);
	args_leftchild = insert_leftchildnode_ast(ast_node, A_FILEPATH);
	while (data.lexer.pptokens[index] && data.lexer.ptype[index] != T_PIPE)
	{
		if (data.lexer.ptype[index] == T_COMMAND)
			break;
		index++;
	}
	init_idx(index, args_leftchild);
	args_rightchild = insert_rightchildnode_ast(ast_node, A_ARGUMENT);
	while (data.lexer.pptokens[index] && data.lexer.ptype[index] != T_PIPE)
		args_utils(&index, args_rightchild);
	return (TRUE);
}

// reds 밑부분 만들기
void	tree_reds(t_astnode *ast_node, int index)
{
	char		**tokens;
	t_astnode	*reds_leftchild;
	t_astnode	*reds_rightchild;
	
	if (ast_node->nodetype != A_REDIRECTIONS)
		return ;
	tokens = data.lexer.pptokens;
	reds_leftchild = insert_leftchildnode_ast(ast_node, A_REDIRECTION); // RED
	reds_rightchild = insert_rightchildnode_ast(ast_node, 0); // REDS
	if (data.lexer.ptype[index] == T_REDIRECTION)
		insert_redschild(reds_leftchild, reds_rightchild, index);
	index++;
	while (data.lexer.ptype[index] != T_PIPE && tokens[index])
	{
		if (data.lexer.ptype[index] == T_REDIRECTION)
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
	if (node)
	{
		delete_ast(node->pleftchild);
		delete_ast(node->prightchild);
		free(node);
	}
}

void free_data_ast(void)
{
	if (data.ast.prootnode)
	{
		delete_ast(data.ast.prootnode);
		ft_bzero(&data.ast, sizeof(t_ast));
	}
}

int	args_utils(int *index, t_astnode *args_rightchild)
{
	int	*type;

	type = data.lexer.ptype;
	if (type[*index] == T_REDIRECTION) // red filename
		(*index)++;
	else
		init_idx(*index, args_rightchild);
	(*index)++;
	return (TRUE);
}
