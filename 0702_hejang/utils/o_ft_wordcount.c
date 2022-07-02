/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_ft_wordcount.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:21:32 by yukim             #+#    #+#             */
/*   Updated: 2022/07/02 19:05:03 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	skip_quote(char	const *str, int *i, int *quote);

int	case_redirection(char const *str, int *i)
{
	if (is_redirection(&str[*i]) == ERROR)
		return (ERROR);
	while (str[*i] && is_redirection(&str[*i]))
		(*i)++;
	return (TRUE);
}

int ft_wordcount(char const *str)
{
	int	ret;
	int	i;
	int	wc;
	int	wc_flag;
	int	quote;

	quote = 0;
	wc_flag = 1;
	i = 0;
	wc = 0;
	while (str[i])
	{
		quote = is_quote(str[i]);
		ret = skip_quote(str, &i, &quote);
		if(ret == TRUE)
			continue;
		else if(ret == data.exit_status)
			return (data.exit_status);
		if (str[i] && is_redirection(&str[i]))
		{
			if (case_redirection(str, &i) == ERROR)
				return (ERROR);
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
			ret = wc_else(str, &i, &quote);
			if (ret == TRUE)
				continue;
			else if (ret == data.exit_status)
				return (data.exit_status);
		}
		if (wc_flag == 1)
			wc++;
	}
	return (wc);
}

static int	skip_quote(char	const *str, int *i, int *quote)
{
	if (str[(*i)] && *quote)
	{
		(*i)++;
		while(str[*i] && *quote != is_quote(str[*i]))
			(*i)++;
		if (str[*i] == '\0' && *quote != is_quote(str[*i]))
		{
			data.exit_status = 1;
			return (data.exit_status);
		if(is_quote(str[(*i) + 1]))
		{
			(*i)++;
			return (TRUE);
		}
	}
	return (FALSE);
}

static int wc_else(char const *str, int *i, int *quote)
{
	while (str[*i] && !is_ifs(str[*i]) && !is_redirection(&str[*i]) \
			&& !is_pipe(&str[*i]))
	{
		(*i)++;
		*quote = is_quote(str[*i]);
		if (str[*i] && *quote)
		{
			(*i)++;
			while(str[*i] && *quote != is_quote(str[*i]))
				(*i)++;
			if (str[*i] == '\0' && *quote != is_quote(str[*i]))
			{
				data.exit_status = 1;
				return (data.exit_status);
			}
			if(is_quote(str[(*i) + 1]))
			{
				(*i)++;
				return (TRUE);
			}
		}
	}
}
