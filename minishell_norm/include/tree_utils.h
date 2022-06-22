/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 03:26:41 by hejang            #+#    #+#             */
/*   Updated: 2022/06/15 20:04:23 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_UTILS_H
# define TREE_UTILS_H

# include "minishell_define.h"

t_astnode*	insert_leftchildnode_ast(t_astnode* p_parentnode, int nodetype);
t_astnode*	insert_rightchildnode_ast(t_astnode* p_parentnode, int nodetype);

int			init_idx(int index, t_astnode *node);
void		tree_cmd(t_astnode *ast_node, int index);
void		tree_reds(t_astnode *ast_node, int index);
void		init_ast(void);
int			tree_args(t_astnode *ast_node, int index);
int			recur_pipe(t_astnode *ast_node, int index); // 가장 처음은 초기화된 rootNode, index = 0 이 들어옴
// void deletet_ast(t_ast* p_ast);
// void deletet_astnode(t_astnode** pㅜode); // 댕글링 포인터 처리 위해서 이중포인터로 전달
void	delete_ast(t_astnode *node);
void	free_ast(t_ast *ast);

#endif
