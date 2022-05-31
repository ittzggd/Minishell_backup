/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:21:32 by yukim             #+#    #+#             */
/*   Updated: 2022/05/31 13:21:49 by hejang           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			while (str[i] && quote != 0)
			{
				i++;
				if (quote == is_quote(str[i]))
					quote = 0;
			}
			i++;
		}
		else if (str[i] && is_redirection(&str[i]))
		{
			if (is_redirection(&str[i]) == ERROR)
				return (ERROR);
			while (str[i] && is_redirection(&str[i]))
				i++;
		}
		else if (str[i] && is_ifs(str[i]))
		{
			while (str[i] && is_ifs(str[i]))
				i++;
			continue ;
		}
		else if (str[i] && is_pipe(&str[i]))
			i++;
		else
		{
			while (str[i] && !is_ifs(str[i]) && !is_redirection(&str[i]) && !is_quote(str[i]) && !is_pipe(&str[i]))
				i++;
		}
		wc++;
	}
	return (wc);
}
