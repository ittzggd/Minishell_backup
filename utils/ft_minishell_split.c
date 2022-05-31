/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:40:41 by yukim             #+#    #+#             */
/*   Updated: 2022/05/31 19:19:57 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] && is_quote(str[i]))
		{
			quote = is_quote(str[i]);
			while (str[i] && quote != 0)
			{
				i++;
				if (quote == is_quote(str[i]))
					quote = 0;
			}
			i++;
			return (i);
		}
		else if (str[i] && is_redirection(&str[i]))
		{
			if (is_redirection(&str[i]) == ERROR)
				return (ERROR);
			while (str[i] && is_redirection(&str[i]))
				i++;
			return (i);
		}
		else if (str[i] && is_pipe(&str[i]))
		{
			if (is_pipe(&str[i]) == ERROR)
				return (ERROR);
			i++;
			return (i);
		}
		else
		{
			while (str[i] && !is_ifs(str[i]) && !is_redirection(&str[i]) && !is_quote(str[i]) && !is_pipe(&str[i]))
				i++;
			return (i);
		}
	}
	return (i);
}

int	ft_split_str(char *str, char **ret)
{
	int	i;
	int	j;
	int	wlen;
	int	quote;

	i = 0;
	wlen = 0;
	quote = 0;
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
		ret[i] = (char *)malloc(sizeof(char) * (wlen + 1));
		if (!ret[i])
			return (i);
		while (j < wlen)
		{
			ret[i][j] = *str;
			j++;
			str++;
		}
		ret[i][j] = '\0';
		i++;
	}
	ret[i] = NULL;
	return (i);
}

// char	**ft_minishell_split(char const *str)
// {
// 	int		wc;
// 	int		split_res;
// 	char	**ret;

// 	if (!str)
// 		return (NULL);
// 	wc = ft_wordcount(str); // 1. 단어 개수 세기
// 	if (wc == ERROR)
// 		return (NULL);
// 	ret = (char **)malloc(sizeof(char *) * (wc + 1));
// 	if (!ret)
// 		return (NULL); // 2. ret malloc => NULL 체크
// 	split_res = ft_split_str((char *)str, ret);
// 	if (split_res != wc)
// 	{
// 		ft_free_all(ret);
// 		ret = NULL;
// 	}
// 	return (ret);
// }
