/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 03:23:51 by hejang            #+#    #+#             */
/*   Updated: 2022/06/05 14:26:43 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./include/tree_utils.h"

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

int	init_idx(int index, t_astnode *node)
{
	int	*tmp;
	int	i;
	int	existing_size;

	i = 0;
	existing_size = 0;
	if (!node->pvalue_index) // 근데 사실 우리가 insertnode_에서 초기화를 시켜주기 때문에 정확하게 널 포인터는 아니지 않을까...?
		tmp = (int *)ft_calloc(2, sizeof(int));
	else
	{
		existing_size = sizeof(node->pvalue_index) / sizeof(int);
		tmp = (int *)ft_calloc(existing_size + 2, sizeof(int));
	}
	if (!tmp)
		return (ERROR);
	while (i < existing_size) // 복사
	{
		tmp[i] = node->pvalue_index[i];
		i++;
	}
	tmp[i] = index;
	tmp[i + 1] = -1;
	if(node->pvalue_index)
		free(node->pvalue_index);
	node->pvalue_index = tmp;
	return (TRUE);
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
