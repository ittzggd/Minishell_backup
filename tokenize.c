/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:20:55 by yukim             #+#    #+#             */
/*   Updated: 2022/05/31 13:49:16 by hejang           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
0. ft_split을 공백 탭 개행 기준 토큰화 하기 => 왜냐면 파일로 들어올수도 있다
1. 왼쪽 큰따옴표, 작은따옴표 체크
2. 오른쪽 큰따옴표, 작은 따옴표 체크
3. split Return 이중 포인터 받을 애 필요 -> 
*/

char	**tokenize_input(t_data *data, char *input)
{
	data->tokens = ft_minishell_split(input);
	if (!data->tokens)
		return (NULL);
	return (data->tokens);
}
/*

tokenize input함수와 ft_minishell_split 을 합쳐주는 건 어떨지 의논하기
그리고 data->tokens_cnt에 ft_minishell_split의 wc+1 = tokens length 저장하기

*/
