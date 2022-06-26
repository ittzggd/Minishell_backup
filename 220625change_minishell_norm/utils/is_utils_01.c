/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:36:09 by yukim             #+#    #+#             */
/*   Updated: 2022/06/26 13:41:42 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_ifs(const char c)
{
	return ((c == '\n' || c == '\t' || c == ' '));
}

int	is_redirection(const char *s)
{
	int	r_cnt;

	r_cnt = 0;
	while (*s == '<' || *s == '>')
	{
		r_cnt++;
		// 밑의 경우일 경우 에러 문구 출력 후 다음 입력 받기 (readline) 
		if (r_cnt > 2 || (r_cnt == 2 && *s != *(s - 1)))  // <>    ><   >>>>> 경우 예외처리
			return (ERROR); //// redirection ERROR : zsh: parse error near `>'
		s++;
	}
	return (r_cnt);
}

int	is_quote(const char c)
{
	if (c == '\'')
		return (SINGLE_QUOTE);
	else if (c == '\"')
		return (DOUBLE_QUOTE);
	return (FALSE);
}

int	is_pipe(const char *s)
{
	int	p_cnt;

	p_cnt = 0;
	while (*s == '|')
	{
		p_cnt++;
		if (p_cnt > 1)
			return (ERROR);
		s++;
	}
	return (p_cnt);
}
