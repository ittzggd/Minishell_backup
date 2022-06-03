/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 03:26:41 by hejang            #+#    #+#             */
/*   Updated: 2022/06/03 15:00:47 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_UTILS_H
# define TREE_UTILS_H

# include "minishell_define.h"

t_astnode*	insert_leftchildnode_ast(t_astnode* p_parentnode, int nodetype);
t_astnode*	insert_rightchildnode_ast(t_astnode* p_parentnode, int nodetype);
int			init_idx(int index, t_astnode *node)
// void deletet_ast(t_ast* p_ast);
// void deletet_astnode(t_astnode** pㅜode); // 댕글링 포인터 처리 위해서 이중포인터로 전달

#endif