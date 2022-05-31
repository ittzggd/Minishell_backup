/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:36:15 by hejang            #+#    #+#             */
/*   Updated: 2022/05/31 18:38:39 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
0. ft_split을 공백 탭 개행 기준 토큰화 하기 => 왜냐면 파일로 들어올수도 있다
1. 왼쪽 큰따옴표, 작은따옴표 체크
2. 오른쪽 큰따옴표, 작은 따옴표 체크
3. split Return 이중 포인터 받을 애 필요 -> 
*/

void	tokenize_input(t_data *data, char *input)
{
	int		split_index;

	if (!input)
		return (NULL);
	data->tokens_cnt = ft_wordcount(input); // 1. 단어 개수 세기
	if (data->tokens_cnt == ERROR)
		return (NULL);
	data->plexer->pptokens = (char **)malloc(sizeof(char *) * (data->tokens_cnt + 1));
	if (!data->plexer->pptokens)
		return (NULL); // 2. data->tokens malloc => NULL 체크
	split_index = ft_split_str((char *)input, data->plexer->pptokens);
	if (split_index != data->tokens_cnt)
	{
		ft_free_all(data->plexer->pptokens);
		data->plexer->pptokens = NULL;
	}
}
