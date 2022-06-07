/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:21:32 by yukim             #+#    #+#             */
/*   Updated: 2022/06/07 21:28:05 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	case_quote(char const *str, int *i)
{
	int	quote;

	quote = is_quote(str[*i]);
	while (str[*i] && quote != 0)
	{
		(*i)++;
		if (str[*i] == '\0') // "H \0
			return (ERROR); // 닫은 따옴표가 없을 경우
		if (quote == is_quote(str[*i]))
			quote = 0;
	}
	(*i)++;
	return (TRUE);
}

int	case_redirection(char const *str, int *i)
{
	if (is_redirection(&str[*i]) == ERROR)
		return (ERROR);
	while (str[*i] && is_redirection(&str[*i]))
		(*i)++;
	return (TRUE);
}

int	ft_wordcount(char const *str)
{
	int	i;
	int	wc;
	int	wc_flag;
	// int	quote;

	wc_flag = 1;
	i = 0;
	wc = 0;
	while (str[i])
	{
		if (str[i] && is_quote(str[i]))
		{

			// quote = is_quote(str[i]);
			// while (str[i] && quote != 0)
			// {
			// 	i++;
			// 	if (quote == is_quote(str[i]))
			// 		quote = 0;
			// }
			// i++;
			if (case_quote(str, &i) == ERROR)
				return (ERROR);
			wc_flag = 0;
		}
		else if (str[i] && is_redirection(&str[i]))
		{
			if (case_redirection(str, &i) == ERROR)
				return (ERROR);
			// if (is_redirection(&str[i]) == ERROR)
			// 	return (ERROR);
			// while (str[i] && is_redirection(&str[i]))
			// 	i++;
			wc_flag = 1;
		}
		else if (str[i] && is_ifs(str[i]))
		{
			while (str[i] && is_ifs(str[i]))
				i++;
			wc_flag = 1;
			continue ;
		}
		else if (str[i] && is_pipe(&str[i]))
		{
			if (is_pipe(&str[i]) == ERROR)
				return (ERROR);
			i++;
			wc_flag = 1;
		}
		else
		{
			while (str[i] && !is_ifs(str[i]) && !is_redirection(&str[i]) \
						&& !is_quote(str[i]) && !is_pipe(&str[i]))
				i++;
		}
		if (wc_flag == 1)
			wc++;
	}
	return (wc);
}
