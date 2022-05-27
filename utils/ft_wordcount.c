/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:21:32 by yukim             #+#    #+#             */
/*   Updated: 2022/05/27 13:15:47 by yukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_ifs(const char c)
{
	return ((c == '\n' || c == '\t' || c == ' '));
}

static int	is_redirection(const char *s)
{
	int	r_cnt;

	r_cnt = 0;
	while(*s == '<' || *s == '>')
	{
		r_cnt++;
		// 밑의 경우일 경우 에러 문구 출력 후 다음 입력 받기 (readline) 
		if (r_cnt > 2 || (r_cnt == 2 && *s != *(s - 1)))  // <>    ><   >>>>> 경우 예외처리
			return (ERROR); //// redirection ERROR : zsh: parse error near `>'
		s++;
	}
	return (r_cnt);
}

static int	is_quote(const char c)
{
	if (c == '\'')
		return (SINGLE_QUOTE);
	else if(c == '\"')
		return (DOUBLE_QUOTE);
	return (FALSE);
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
		if (str[i] && is_quote(str[i]))
		{
			quote = is_quote(str[i]);
			while(str[i] && quote != 0)
			{
				i++;
				if(quote == is_quote(str[i]))
					quote = 0;
			}
			i++;
			wc++;
		}
		else if (str[i] && is_redirection(&str[i]))
		{
			if (is_redirection(&str[i]) == ERROR)
				return (ERROR);
			while (str[i] && is_redirection(&str[i]))
				i++;
			wc++;
		}
		else if (str[i] && is_ifs(str[i]))
		{
			while (str[i] && is_ifs(str[i]))
				i++;
		}	
		else 
		{
			while (str[i] && !is_ifs(str[i]) && !is_redirection(&str[i]) && !is_quote(str[i]))
				i++;
			wc++;
		}
	}
	return (wc);
}