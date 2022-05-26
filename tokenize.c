/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:20:55 by yukim             #+#    #+#             */
/*   Updated: 2022/05/26 17:20:55 by yukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
0. ft_split을 공백 탭 개행 기준 토큰화 하기 => 왜냐면 파일로 들어올수도 있다
1. 왼쪽 큰따옴표, 작은따옴표 체크
2. 오른쪽 큰따옴표, 작은 따옴표 체크
3. split Return 이중 포인터 받을 애 필요 -> 
*/

char	**tokenize_input(char *input)
{
	char **tokens;

	tokens = ft_minishell_split(input);
	if(!tokens)
		return(NULL);
	return (tokens);
}