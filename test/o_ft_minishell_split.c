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
			i++;
			while(!is_quote(str[i]))
				i++;
		// 	case_quote(str, &i);
		// 	wc_flag = 0;
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
				if (is_quote(str[i]))
					continue ;
			}
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

	i = 0;
	wlen = 0;
	while (*str)
	{
		if (*str && is_ifs(*str))
		{
			while (*str && is_ifs(*str))
				str++;
			if (*str == '\0')
				break ;
		}
		j = 0;
		wlen = ft_wordlen(str);
		tokens[i] = (char *)malloc(sizeof(char) * (wlen + 1));
		if (!tokens[i])
			return (i);
		while (j < wlen)
		{
			tokens[i][j] = *str;
			j++;
			str++;
		}
		tokens[i][j] = '\0';
		i++;
	}
	tokens[i] = NULL;
	return (i);
}
