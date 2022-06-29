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

t_astnode* insert_leftchildnode_ast(t_astnode* p_parentnode, int nodetype)
{
	t_astnode *pchild;

	if (p_parentnode->pleftchild) 
	{
		printf ("LeftChild Node already exist \n");
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
		printf ("RightChild Node already exist \n");
		free_all_in_data();
		exit(1);
	}
	calloc_nullcheck(&pchild, 1, sizeotf(t_astnode));
	pchild->nodetype = nodetype;
	p_parentnode->prightchild = pchild;
	return (pchild);
}

int	init_idx(int index, t_astnode *node) //예가 머하는 함수였드라...?
{
	int	*tmp;
	int	i;
	int	existing_size;

	i = 0;
	existing_size = 0;
	if (!node->pvalue_index)
		calloc_nullcheck(&tmp, 2, sizeof(int));
	else
	{
		while(node->pvalue_index[existing_size] != -1)
			existing_size++;
		calloc_nullcheck(&tmp, existing_size + 2, sizeof(int));
	}
	while (i < existing_size)
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
