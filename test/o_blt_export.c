/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_blt_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:35 by yukim             #+#    #+#             */
/*   Updated: 2022/06/15 15:00:16 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

int	ft_export(t_data *data, t_astnode *args_node) // export USER=1 HI=2 HOME=3
{
	char	*input;
	char	*key;
	char	*value;
	char	*p_equal;
	int		init_flag;
	int		i;

	init_flag = FALSE;
	data->exit_status = 0;
	input = data->plexer->pptokens[args_node->prightchild->pvalue_index[1]];
	if (args_node->prightchild->pvalue_index[1] == END) // 아스키 코드순으로 출력 = env 실행
	{
		ft_env(data, TRUE);
		return (data->exit_status);	 // exit_status : 성공
	}
	i = 1;
	while (args_node->prightchild->pvalue_index[i] != -1)
	{
		input = remove_quote(data->plexer->pptokens[args_node->prightchild->pvalue_index[i]]);
		init_flag = init_envp(input, &key, &value);
		if (init_flag == ERROR)
		{
			data->exit_status = 1;
			return (data->exit_status);
		}
		if (!is_valid_env(key))
		{
			data->exit_status = 1;
			return (data->exit_status);
		}
		insert_envv(data, key, value, init_flag);
		if (!value)
			continue ;
		else
		{
			free(key);
			free(value);
		}
		i++;
	}
	return (data->exit_status);
}
