/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 03:26:41 by hejang            #+#    #+#             */
/*   Updated: 2022/07/12 17:24:33 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "minishell_define.h"

int			init_idx(int index, t_astnode *node);
t_astnode	*insert_leftchildnode_ast(t_astnode *p_parentnode, int nodetype);
t_astnode	*insert_rightchildnode_ast(t_astnode *p_parentnode, int nodetype);

void		init_ast(t_data *data);
int			recur_pipe(t_data *data, t_astnode *ast_node, int index);
void		tree_cmd(t_data *data, t_astnode *ast_node, int index);
void		tree_reds(t_data *data, t_astnode *ast_node, int index);
int			tree_args(t_data *data, t_astnode *ast_node, int index);

void		goto_redirection(t_data *data, t_astnode *red_node);
void		postorder_travel_reds(t_data *data, t_astnode *reds_node);
void		postorder_travel_command(t_data *data, t_astnode *cmdnode);
void		postorder_travel_ast(t_data *data, t_astnode *ast_node);

void		delete_astnode(t_astnode *node);
void		free_data_ast(t_data *data);

#endif
