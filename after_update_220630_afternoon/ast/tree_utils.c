/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_tree_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 03:23:51 by hejang            #+#    #+#             */
/*   Updated: 2022/06/30 06:07:00 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void pvalue_idx_init_idx(int *tmp, int idx, t_astnode *node, int size);

t_astnode* insert_leftchildnode_ast(t_astnode* p_parentnode, int nodetype)
{
	t_astnode *pchild;

	if (p_parentnode->pleftchild) 
	{
		ft_error_message("LeftChild Node already exist \n", 1);
		free_all_in_data();
		exit(1);
	}
	calloc_nullcheck(&pchild, 1, sizeotf(t_astnode));
	pchild->nodetype = nodetype;
	p_parentnode->pleftchild = pchild;
	return (pchild);
}

t_astnode* insert_rightchildnode_ast(t_astnode* p_parentnode, int nodetype)
{
	t_astnode *pchild;

	if (p_parentnode->prightchild)
	{
		ft_error_message("RightChild Node already exist \n", 1);
		free_all_in_data();
		exit(1);
	}
	calloc_nullcheck(&pchild, 1, sizeotf(t_astnode));
	pchild->nodetype = nodetype;
	p_parentnode->prightchild = pchild;
	return (pchild);
}

int	init_idx(int index, t_astnode *node)
{
	int	*tmp;
	int	existing_size;

	existing_size = 0;
	if (!node->pvalue_index)
		calloc_nullcheck(&tmp, 2, sizeof(int));
	else
	{
		while(node->pvalue_index[existing_size] != -1)
			existing_size++;
		calloc_nullcheck(&tmp, existing_size + 2, sizeof(int));
	}
	pvalue_idx_init_idx(tmp, index, node, existing_size);
	return (TRUE);
}

static void pvalue_idx_init_idx(int *tmp, int idx, t_astnode *node, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		tmp[i] = node->pvalue_index[i];
		i++;
	}
	tmp[i] = idx;
	tmp[i + 1] = -1;
	if (node->pvalue_index)
		free(node->pvalue_index);
	node->pvalue_index = tmp;
}
