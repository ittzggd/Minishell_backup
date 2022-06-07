/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:40:41 by yukim             #+#    #+#             */
/*   Updated: 2022/06/05 09:47:572 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	1. 단어 개수 세기
	2. ret malloc => NULL 체크
	3. 
	3-1. word length 구해서 ret[i] malloc & NULL CHECK  
	3-2. ret[i]에 length만큼 copy
		3-1, 3-2 를 ft_strcup 가능?
		조건들은 wordcount 구조 차용 가능
	4. 과정 중 실패시 free
		ft_split_str의 ret된 i < wc인 경우
	3-4. 성공시 return ret
	*/

int	ft_wordlen(char const *str)
{
	int	i;
	int	wc_flag;

	i = 0;
	wc_flag = 1;
	while (str[i])
	{
		if (str[i] && is_quote(str[i]))
		{
			// quote = is_quote(str[i]);
			// while (str[i] && quote != 0)
			// {
			// 	i++;
			// 	if (quote == is_quote(str[i]))
			// 		xsquote = 0;
			// }
			// i++;
			case_quote(str, &i);
			wc_flag = 0;
			// return (i);
		}
		else if (str[i] && is_redirection(&str[i]))
		{
			// if (is_redirection(&str[i]) == ERROR)
			// 	return (ERROR);
			// while (str[i] && is_redirection(&str[i]))
			// 	i++;
			case_redirection(str, &i);
			wc_flag = 1;
			// return (i);
		}
		else if (str[i] && is_pipe(&str[i]))
		{
			// if (is_pipe(&str[i]) == ERROR)
			// 	return (ERROR);
			// i++;
			// return (i);
			return (1);
		}
		else if (str[i] && is_ifs(str[i]))
			wc_flag = 1;
		else
		{
			while (str[i] && !is_ifs(str[i]) && !is_redirection(&str[i]) \
						&& !is_quote(str[i]) && !is_pipe(&str[i]))
			{
				i++;
				if (is_quote(str[i]))
					continue ;
			}// return (i);
		}
		if (wc_flag == 1)
			break ;
	}
	return (i);
}

int	ft_split_str(char *str, char **tokens)
{
	int	i;
	int	j;
	int	wlen;
	// int	quote;

	i = 0;
	wlen = 0;
	// quote = 0;
	while (*str)
	{
		if (*str && is_ifs(*str))
		{
			while (*str && is_ifs(*str))
				str++;
			if (*str == '\0')
				break ;       // str의 맨 마지막에 space인 경우 탈출 하게끔
		}
		j = 0;
		wlen = ft_wordlen(str);
		tokens[i] = (char *)malloc(sizeof(char) * (wlen + 1));
		if (!tokens[i])
			return (i);
		// while (j < wlen)
		// {
		// 	tokens[i][j] = *str;
		// 	j++;
		// 	str++;
		// }
		// tokens[i][j] = '\0';
		ft_strlcpy(tokens[i], str, wlen + 1);
		str = str + wlen + 1;
		i++;
	}
	tokens[i] = NULL;
	return (i);
}


