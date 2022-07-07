/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_blt_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:41 by yukim             #+#    #+#             */
/*   Updated: 2022/07/03 17:10:05 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

static int	is_prev_pipe__ft_unset_util(t_astnode *args_node);
static void	ft_unset_with_args(t_astnode *args_node);

int	ft_unset(t_astnode *args_node)
{
	g_data.exit_status = 0;
	if (args_node->prightchild->pvalue_index[1] == END)
		return (g_data.exit_status);
	ft_unset_with_args(args_node);
	return (g_data.exit_status);
}

static void	ft_unset_with_args(t_astnode *args_node)
{
	int			i;
	char		*key;
	char		*rm_quote_key;
	t_envv_node	*env_node;

	i = 1;
	while (args_node->prightchild->pvalue_index[i] != END)
	{
		key = g_data.lexer.pptokens[args_node->prightchild->pvalue_index[i]];
		rm_quote_key = remove_quote(key);
		env_node = get_el_node(g_data.envv_list, rm_quote_key);
		if (rm_quote_key)
			free(rm_quote_key);
		if (!env_node)
			g_data.exit_status = 1;
		else
		{
			if (is_prev_pipe__ft_unset_util(args_node) == TRUE)
				return ;
			remove_ll_element(&g_data.envv_list, env_node->key);
		}
		i++;
	}
}

static int	is_prev_pipe__ft_unset_util(t_astnode *args_node)
{
	int	position;

	position = args_node->prightchild->pvalue_index[0] - 1;
	if (position < 0)
		return (FALSE);
	if (g_data.lexer.ptype[position] == T_PIPE)
		return (TRUE);
	return (FALSE);
}
