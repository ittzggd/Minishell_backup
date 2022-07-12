/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   postorder_travel_command.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:30:40 by yukim             #+#    #+#             */
/*   Updated: 2022/07/12 17:25:35 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

void	postorder_travel_command(t_data *data, t_astnode *cmdnode)
{
	if (cmdnode)
	{
		postorder_travel_reds(data, cmdnode->pleftchild);
		if (cmdnode->prightchild->prightchild->pvalue_index)
			exec_cmd(data, cmdnode->prightchild);
	}
}

void	postorder_travel_reds(t_data *data, t_astnode *reds_node)
{
	if (reds_node->pleftchild)
	{
		goto_redirection(data, reds_node->pleftchild);
	}
	if (reds_node->prightchild)
	{
		postorder_travel_reds(data, reds_node->prightchild);
	}
}

void	goto_redirection(t_data *data, t_astnode *red_node)
{
	char	*red;
	char	*filename;

	if (!red_node->prightchild->pvalue_index)
		return ;
	red = data->lexer.pptokens[red_node->pleftchild->pvalue_index[0]];
	filename = data->lexer.pptokens[red_node->prightchild->pvalue_index[0]];
	if (ft_strncmp(red, "<", -1))
		in_red(filename);
	else if (ft_strncmp(red, ">", -1))
		out_red(filename);
	else if (ft_strncmp(red, ">>", -1))
		append_red(filename);
	else if (ft_strncmp(red, "<<", -1))
		heredoc(filename);
}
