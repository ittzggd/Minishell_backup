/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:21:32 by yukim             #+#    #+#             */
/*   Updated: 2022/05/26 20:21:32 by yukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_ifs(char c)
{
	return ((c == '\n' || c == '\t' || c == ' '));
}

static int	is_redirection(char *s, int quote)
{
	int	r_cnt;

	r_cnt = 0;
	if(quote != 0)
		return (FALSE); // 정상
	while(*s == '<' || *s == '>')
	{
		r_cnt++;
		// 밑의 경우일 경우 에러 문구 출력 후 다음 입력 받기 (readline) 
		if (r_cnt > 2 || (r_cnt == 2 && *s != *(s - 1)))  // <>    ><   >>>>> 경우 예외처리
			return (ERROR); //// redirection ERROR : zsh: parse error near `>'
		s++;
	}
	// if(*s != '<' || *s != '>')
	// 	return (FALSE);
	return (r_cnt);
}

int	ft_wordcount(char const *str)
{
	int	i;
	int	wc;
	int	quote;

	i = 0;
	quote = 0;
	wc = 0;
	while (str[i])
	{
		if (str[i] && is_ifs(str[i]) == FALSE && quote == 0)
		{
			wc++;
			while (str[i] && (is_ifs(str[i]) == FALSE || quote > 0))
			{
				if (str[i] == '\"' && quote == 0)
					quote = DOUBLE_QUOTE;
				else if (str[i] == '\'' && quote == 0)
					quote = SINGLE_QUOTE;
				else if (str[i] == '\"' && quote == DOUBLE_QUOTE)
					quote = 0;
				else if (str[i] == '\'' && quote == SINGLE_QUOTE)
					quote = 0;
				else if (is_redirection((char *)str + i, quote) > 0)
				{ // >>   ,   <<   ,   >   ,  <
					wc++;
					while(str[i] && is_redirection((char *)str + i, quote))
						i++;
					if (str[i] && is_ifs(str[i]) == FALSE)
						wc++;
					if ((str[i] == '\'' && str[i] == '\"') || is_ifs(str[i]))
						continue ; 
				}
				else if (is_redirection((char *)str + i, quote) == ERROR)
					return (ERROR);
				i++;
			}			
		}
		else
			i++; // 공백 다음 문자위치로 이동
	}
	return (wc);
}