/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:36:15 by hejang            #+#    #+#             */
/*   Updated: 2022/05/31 16:38:13 by hejang           ###   ########seoul.kr  */
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
	int		split_res;

	if (!input)
		return (NULL);
	data->tokens_cnt = ft_wordcount(input); // 1. 단어 개수 세기
	if (data->tokens_cnt == ERROR)
		return (NULL);
	data->tokens = (char **)malloc(sizeof(char *) * (data->tokens_cnt + 1));
	if (!data->tokens)
		return (NULL); // 2. data->tokens malloc => NULL 체크
	split_res = ft_split_str((char *)input, data->tokens);
	if (split_res != data->tokens_cnt)
	{
		ft_free_all(data->tokens);
		data->tokens = NULL;
	}
}
/*

tokenize input함수와 ft_minishell_split 을 합쳐주는 건 어떨지 의논하기
그리고 data->tokens_cnt에 ft_minishell_split의 wc+1 = tokens length 저장하기

*/
