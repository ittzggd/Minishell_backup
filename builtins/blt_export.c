/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:35 by yukim             #+#    #+#             */
/*   Updated: 2022/06/07 21:27:39 by hejang           ###   ########.fr       */
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

	input = data->plexer->pptokens[args_node->pvalue_index[1]];
	if(!input) // 아스키 코드순으로 출력 = env 실행
	{
		ft_env(data, TRUE);
		return (0); // exit_status : 성공
	}
	
	i = 1;
	while (args_node->pvalue_index[i] != -1)
	{
		input = data->plexer->pptokens[args_node->pvalue_index[i]];
		if (ft_strchr(input, '=')) // 키와 값 저장
		{
			init_flag = TRUE;
			// 일단은 quote 제거
			if (is_quote(*input))
				input++; // 앞 부분 따옴표 제거
			// 키와 값을 분리하기 == ft_split시 = 기준 분린
			splited_input = ft_split(input, '=');
			if (!splited_input)
				return (ERROR);
			key = splited_input[0];
			value = splited_input[1];
			insert_envv(data, key, value);
		}
		if (get_envv(data, args_node->pvalue_index[i]))
		{
			is_valid_env();
		}
		if (init_flag == TRUE)
		{
			// 값 저장
		}
		// envv_list에 키 저장
	}
		

}
