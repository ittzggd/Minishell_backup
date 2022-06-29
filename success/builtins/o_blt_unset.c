/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_blt_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:41 by yukim             #+#    #+#             */
/*   Updated: 2022/06/28 18:46:56 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

int	ft_unset(t_astnode *args_node) //astNode로 받는 이유 : unset USER HI HOME
{
	int		i;
	char	*key;
	char	*rm_quote_key;
	t_envv_node	*env_node;

	data->exit_status = 0;
	if (args_node->prightchild->pvalue_index[1] == END)
		return (data->exit_status); // exit_status : 성공
	i = 1;
	while (args_node->prightchild->pvalue_index[i] != END)
	{
		key = data->lexer.pptokens[args_node->prightchild->pvalue_index[i]];
		rm_quote_key = remove_quote(key);
		env_node = get_el_node(data->envv_list, rm_quote_key);
		if (rm_quote_key != key)
			free(rm_quote_key);
		if (!env_node)
		{
			data->exit_status = 1;
			i++;
			continue ;
			//return (1); // exit_status : 실패
		}
		// 파이프 다음인가?
		if (data->lexer.ptype[args_node->prightchild->pvalue_index[0] - 1] == T_PIPE)
			return (data->exit_status); // exit_status : 성공
		remove_ll_element(&data->envv_list, env_node->key);
		i++;
	}
	return (data->exit_status); // exit_status : 성공
}