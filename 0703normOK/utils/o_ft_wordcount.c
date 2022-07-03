/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_ft_wordcount.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:21:32 by yukim             #+#    #+#             */
/*   Updated: 2022/07/03 17:51:54 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	skip_quote(char	const *str, int *i, int *quote);
static int	red_ifs_pipe(char const *str, int *i, int *quote, int *wc_flag);
static int wc_else(char const *str, int *i, int *quote);
static	int	get_wc(char const *str, int *i, int *quote, int *wc_flag, int *wc);

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
		ret = get_wc(str, &i, &quote, &wc_flag, &wc);
		if (ret == CONTINUE)
			continue ;
		else if (ret == ERROR)
		{
			g_data.exit_status = 1;
			return (g_data.exit_status);
		}
	}
	return (wc);
}

static	int	get_wc(char const *str, int *i, int *quote, int *wc_flag, int *wc)
{
	int	ret;

	*quote = is_quote(str[*i]);
	ret = skip_quote(str, i, quote);
	if (ret == CONTINUE || ret == ERROR)
		return (ret);
	ret = red_ifs_pipe(str, i, quote, wc_flag);
	if (ret == CONTINUE || ret == ERROR)
		return (ret);
	else if (ret == FALSE)
	{
		ret = wc_else(str, i, quote);
		if (ret == CONTINUE || ret == ERROR)
			return (ret);
	}
	if (*wc_flag == 1)
		(*wc)++;
	return (TRUE);
}


static int	skip_quote(char	const *str, int *i, int *quote)
{
	if (str[*i] && *quote)
	{
		(*i)++;
		while (str[*i] && *quote != is_quote(str[*i]))
			(*i)++;
		if (str[*i] == '\0' && *quote != is_quote(str[*i]))
			return (ERROR);
		if (is_quote(str[(*i) + 1]))
		{
			(*i)++;
			return (CONTINUE);
		}
	}
	return (TRUE);

}

static int	red_ifs_pipe(char const *str, int *i, int *quote, int *wc_flag)
{
	if (str[*i] && is_redirection(&str[*i]))
	{
		if (case_redirection(str, i) == ERROR)
			return (ERROR);
		*wc_flag = 1;
		return (TRUE);
	}
	else if (str[*i] && is_ifs(str[*i]))
	{
		while (str[*i] && is_ifs(str[*i]))
			(*i)++;
		*wc_flag = 1;
		return (CONTINUE);
	}
	else if (str[*i] && is_pipe(&str[*i]))
	{
		if (is_pipe(&str[*i]) == ERROR)
			return (ERROR);
		(*i)++;
		*wc_flag = 1;
		return (TRUE);
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
			while (str[*i] && *quote != is_quote(str[*i]))
				(*i)++;
			if (str[*i] == '\0' && *quote != is_quote(str[*i]))
				return (ERROR);
			if (is_quote(str[(*i) + 1]))
			{
				(*i)++;
				return (CONTINUE);
			}
		}
	}
	return (TRUE);
}
