/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 03:23:51 by hejang            #+#    #+#             */
/*   Updated: 2022/06/01 17:02:57 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_astnode* insert_leftchildnode_ast(t_astnode* p_parentnode, int nodetype)
{
	t_astnode *pchild;

	if (p_parentnode->pleftchild) 
	{
	// printf ("LeftChild Node already exist \n");
	// return (NULL);
	}
	pchild = ft_calloc(1, sizeof(t_astnode));
	if (!pchild)
	{ //error
		return (NULL);
	}
	pchild->nodetype = nodetype;
	p_parentnode->pleftchild = pchild;
	return (pchild);
}

t_astnode* insert_rightchildnode_ast(t_astnode* p_parentnode, int nodetype)
{
	t_astnode *pchild;

	if (p_parentnode->prightchild)
	{
	// printf ("RightChild Node already exist \n");
	// return (NULL);
	}
	pchild = ft_calloc(1, sizeof(t_astnode));
	if (!pchild)
	{ //error
		return (NULL);
	}
	pchild->nodetype = nodetype;
	p_parentnode->prightchild = pchild;
	return (pchild);
}

// void deleteBinTree(BinTree* pBinTree)
// {
// 	if (pBinTree)
// 	{
// 	deleteBinTreeNode(&pBinTree->pRootNode);
// 	free(pBinTree);
// 	memset(pBinTree, 0, sizeof(BinTree));
// 	}
// }

// void deleteBinTreeNode(BinTreeNode** pNode)
// {
// 	if (*pNode)
// 	{
// 	deleteBinTreeNode(&(*pNode)->pLeftChild);
// 	deleteBinTreeNode(&(*pNode)->pRightChild);
// 	free(*pNode);
// 	*pNode = NULL;
// 	}
// }