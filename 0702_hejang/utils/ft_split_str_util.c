/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 19:04:31 by yukim             #+#    #+#             */
/*   Updated: 2022/07/02 19:04:52 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_wordlen(char const *str)
{
	int	i;
	int	wc_flag;
	int quote;

	quote = 0;
	i = 0;
	wc_flag = 1;
	while (str[i])
	{
		quote = is_quote(str[i]);
		if (str[i] && quote)
		{
			i++;
			while(str[i] && quote != is_quote(str[i]))
				i++;
			if (str[i] == '\0' && quote != is_quote(str[i]))
				return (ERROR);
			if(is_quote(str[i+1]))
			{
				i++;
			 	continue;
			}
		}
		if (str[i] && is_redirection(&str[i]))
		{
			case_redirection(str, &i);
			wc_flag = 1;
		}
		else if (str[i] && is_pipe(&str[i]))
		{
			return (1);
		}
		else if (str[i] && is_ifs(str[i]))
			wc_flag = 1;
		else
		{
			while (str[i] && !is_ifs(str[i]) && !is_redirection(&str[i]) \
						&&  !is_pipe(&str[i]))
			{
				i++;
				quote = is_quote(str[i]);
				if (str[i] && quote)
				{
					i++;
					while(str[i] && quote != is_quote(str[i]))
						i++;
					if (str[i] == '\0' && quote != is_quote(str[i]))
						return (ERROR);
					if(is_quote(str[i+1]))
					{
						i++;
						continue;
					}
				}
			}
		}
		if (wc_flag == 1)
			break ;
	}
	return (i);
}
