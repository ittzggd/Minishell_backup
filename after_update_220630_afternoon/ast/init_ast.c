/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_ast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:20:15 by hejang            #+#    #+#             */
/*   Updated: 2022/06/30 06:14:57 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_ast(void)
{
	t_astnode	*root_node;

	calloc_nullcheck(&root_node, 1, sizeof(t_astnode));
	data.ast.prootnode = root_node;
	recur_pipe(root_node, 0);
}

int	recur_pipe(t_astnode *ast_node, int index)
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
