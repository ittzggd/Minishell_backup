/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_blt_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:41 by yukim             #+#    #+#             */
/*   Updated: 2022/07/01 19:22:06 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

static int	is_prev_pipe__ft_unset_util(t_astnode *args_node);

int	ft_unset(t_astnode *args_node) //astNode로 받는 이유 : unset USER HI HOME
{
	int		i;
	char	*key;
	char	*rm_quote_key;
	t_envv_node	*env_node;

	data.exit_status = 0;
	if (args_node->prightchild->pvalue_index[1] == END)
		return (data.exit_status);
	i = 1;
	while (args_node->prightchild->pvalue_index[i] != END)
	{
		key = data.lexer.pptokens[args_node->prightchild->pvalue_index[i]];
		rm_quote_key = remove_quote(key);
		env_node = get_el_node(data.envv_list, rm_quote_key);
		if (rm_quote_key != key)
			free(rm_quote_key);
		if (!env_node)
		{
			data.exit_status = 1;
			i++;
			continue ;
		}
		if (is_prev_pipe__ft_unset_util(args_node) == TRUE)
			return (data.exit_status);
		remove_ll_element(&data.envv_list, env_node->key);
		i++;
	}
	return (data.exit_status);
}

static int	is_prev_pipe__ft_unset_util(t_astnode *args_node)
{
	int	position;

	position = args_node->prightchild->pvalue_index[0] - 1;
	if (position < 0)
		return (FALSE);
	if (data.lexer.ptype[position] == T_PIPE)
		return (TRUE);
	return (FALSE);
}
