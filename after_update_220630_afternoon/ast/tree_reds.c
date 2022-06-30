/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_reds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 03:29:13 by yukim             #+#    #+#             */
/*   Updated: 2022/07/01 03:29:13 by yukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	insert_redschild(t_astnode *reds_leftchild, int index);

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
		insert_redschild(reds_leftchild, index);
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

static int	insert_redschild(t_astnode *reds_leftchild, int index)
{
	t_astnode	*leftchild;
	t_astnode	*rightchild;

	leftchild = insert_leftchildnode_ast(reds_leftchild, A_REDIRECTION_TYPE);
	rightchild = insert_rightchildnode_ast(reds_leftchild, A_FILENAME);
	init_idx(index, reds_leftchild->pleftchild);
	init_idx(index + 1, reds_leftchild->prightchild);
	return (TRUE);
}