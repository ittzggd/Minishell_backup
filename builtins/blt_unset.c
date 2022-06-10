/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:41 by yukim             #+#    #+#             */
/*   Updated: 2022/06/10 17:22:21 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

int	ft_unset(t_data *data, t_astnode *args_node) //astNode로 받는 이유 : unset USER HI HOME
{
	int		i;
	char	*key;
	t_envv_node	*env_node;

	if (args_node->pvalue_index[1] == -1)
		return (0); // exit_status : 성공
	i = 1;
	while (args_node->pvalue_index[i] != -1)
	{
		key = data->plexer->pptokens[args_node->pvalue_index[i]];
		env_node = get_el_node(data->envv_list, key);
		if(!env_node)
			return (1); // exit_status : 실패
		// 파이프 다음인가?
		if (data->plexer->ptype[args_node->pvalue_index[0] - 1] == T_PIPE)
			return (0); // exit_status : 성공
		remove_ll_element(data->envv_list, env_node->key);
		i++;
	}
	return (0); // exit_status : 성공
}
