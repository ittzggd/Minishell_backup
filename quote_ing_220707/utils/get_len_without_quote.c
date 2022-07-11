/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_len_without_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 03:15:19 by hejang            #+#    #+#             */
/*   Updated: 2022/07/11 16:12:17 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	case_double_quote(int quote, int *i, int *ret_len, char *quotestr);
static void	case_single_quote(int quote, int *i, int *ret_len, char *quotestr);
static void	case_not_quote(int *i, int *ret_len, char *quote_str);

int	get_len_without_quote(char *quote_str)
{
	int	i;
	int	ret_len;
	int	quote;

	if (!quote_str)
		return (0);
	i = 0;
	ret_len = 0;
	while (quote_str[i])
	{
		quote = is_quote(quote_str[i]);
		if (quote_str[i] && quote == DOUBLE_QUOTE)
			case_double_quote(quote, &i, &ret_len, quote_str);
		else if (quote_str[i] && quote == SINGLE_QUOTE)
			case_single_quote(quote, &i, &ret_len, quote_str);
		else if (quote_str[i] && quote == FALSE)
		{
			case_not_quote(&i, &ret_len, quote_str);
			continue ;
		}
		i++;
	}
	return (ret_len);
}

static void	case_double_quote(int quote, int *i, int *ret_len, char *quotestr)
{
	(*i)++;
	while (quotestr[*i] && quote != is_quote(quotestr[*i]))
	{
		if (quotestr[*i] == '$' && quotestr[*i + 1] == '?')
			get_len_case_exit_status(i, ret_len);
		else if (quotestr[*i] == '$' && !is_quote(quotestr[*i + 1]))
			get_len_case_replace_env(i, ret_len, quotestr);
		else
		{
			(*i)++;
			(*ret_len)++;
		}
	}
}

static void	case_single_quote(int quote, int *i, int *ret_len, char *quotestr)
{
	(*i)++;
	while (quotestr[*i] && quote != is_quote(quotestr[*i]))
	{
		(*i)++;
		(*ret_len)++;
	}
}

static void	case_not_quote(int *i, int *ret_len, char *quote_str)
{
	if (quote_str[*i] == '$' && quote_str[*i + 1] == '?')
		get_len_case_exit_status(i, ret_len);
	else if (quote_str[*i] == '$' && quote_str[*i + 1] != '\0')
		get_len_case_replace_env(i, ret_len, quote_str);
	else
	{
		(*i)++;
		(*ret_len)++;
	}
}
