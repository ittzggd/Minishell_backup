/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:41 by yukim             #+#    #+#             */
/*   Updated: 2022/06/05 10:43:53 by yukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"



int	ft_unset(t_data *data, t_astnode *args_node)
{
	int		i;
	char	*key;
	char	*env_value;

	if (args_node->pvalue_index[1] == -1)
		return (0); // exit_status : 성공
	i = 1;
	while (args_node->pvalue_index[i] != -1)
	{
		key = data->plexer->pptokens[args_node->pvalue_index[i]];
		env_value = getenv(key);
		if(!env_value)
			return (1); // exit_status : 실패
		// 파이프 다음인가?
		if (data->plexer->ptype[args_node->pvalue_index[0] - 1] == T_PIPE)
			return (0); // exit_status : 성공
		
		// 환경변수의 value가 malloc되었는지에 따라 free, 댕글링 포인터 처리해주기
		// free(env_value);
		i++;
	}
}
/*
1. 유효한 이름?
2. 존재하는 환경변수?
*/
int check_unset_valid(t_data *data, t_astnode *args_node, int i)
{
	char	*key;
	
	key = data->plexer->pptokens[args_node->pvalue_index[i]];
	// 유효한 환경 변수명인지 체크하지 않아도 될듯
	if(!getenv(key)) // 없는 환경변수면 getenv가 알아서 에러 넘버 반환함
		return (ERROR) //"invalid environment variable"
	
}
