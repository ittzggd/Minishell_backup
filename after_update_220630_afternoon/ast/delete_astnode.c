/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_astnode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 03:38:03 by yukim             #+#    #+#             */
/*   Updated: 2022/07/01 03:38:03 by yukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

void	delete_astnode(t_astnode *node)
{
	if (node)
	{
		delete_astnode(node->pleftchild);
		delete_astnode(node->prightchild);
		free(node);
	}
}
