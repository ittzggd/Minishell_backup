/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:35 by yukim             #+#    #+#             */
/*   Updated: 2022/06/09 09:44:13 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

int	ft_export(t_data *data, t_astnode *args_node) // export USER=1 HI=2 HOME=3
{
	char	*input;
	char	**splited_input;
	char	*key;
	char	*value;
	int		init_flag;
	int		i;

	init_flag = FALSE;
	input = data->plexer->pptokens[args_node->pvalue_index[1]];
	if(!input) // 아스키 코드순으로 출력 = env 실행
	{
		ft_env(data, TRUE);
		return (0); // exit_status : 성공
	}
	
	i = 1;
	while (args_node->pvalue_index[i] != -1)
	{
		input = remove_quote(data->plexer->pptokens[args_node->pvalue_index[i]]);
		if (ft_strchr(input, '=')) // 키와 값 저장
		{
			init_flag = TRUE;
			// 키와 값을 분리하기 == ft_split시 = 기준 분린
			splited_input = ft_split(input, '=');
			if (!splited_input)
				return (ERROR);
			key = splited_input[0];
			value = splited_input[1];
		}
		else
		{
			key = input;
			value = NULL;
		}
		if(!is_valid_env(key))
			return (ERROR);
		insert_envv(data, key, value);
		ft_free_all(splited_input);
	}
}
