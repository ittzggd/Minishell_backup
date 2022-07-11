/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:36:07 by yukim             #+#    #+#             */
/*   Updated: 2022/07/11 15:19:12 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	case_double_quote(int quote, int *i, int *ret_len, char *quotestr);
static void	case_single_quote(int quote, int *i, int *ret_len, char *quotestr);
static void	case_not_quote(int *i, int *ret_len, char *quote_str);

char	*remove_quote(char *quote_str)
{
	char	*ret;
	size_t	ret_len;
	int		quote;
	int		i;
	int		j;

	char	*key;
	char	*value;
	int		key_len;

	i = 0;
	j = 0;
	ret_len = get_len_without_quote(quote_str);
	ret = ft_calloc(ret_len + 1, sizeof(char));
	if (!ret)
		ft_error("remove_quote : allocation failed\n");
	while (quote_str[i])
	{
		quote = is_quote(quote_str[i]);
		if (quote_str[i] && quote == DOUBLE_QUOTE)
		{
			
		}
		else if (quote_str[i] && quote == SINGLE_QUOTE)
		{
			i++;
			while (quote_str[i] && quote != is_quote(quote_str[i]))
			{
				ret[j] = quote_str[i];
				i++;
				j++;
			}
		}
		else if (quote_str[i] && quote == FALSE)
		{
			if (quote_str[i] == '$' && quote_str[i + 1] == '?')
				rm_quote_case_exit_status(&i, &j, ret);
			else if (quote_str[i] == '$' && quote_str[i + 1] != '\0')
				rm_quote_case_replace(&i, &j, quote_str, ret);
			else
			{
				ret[j] = quote_str[i];
				i++;
				j++;
			}
			continue ;
		}
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

static void	case_double_quote(int quote, int *i, int *ret_len, char *quotestr)
{
	i++;
	while (quote_str[i] && quote != is_quote(quote_str[i]))
	{
		if (quote_str[i] == '$' && quote_str[i + 1] == '?')
			rm_quote_case_exit_status(&i, &j, ret);
		else if (quote_str[i] == '$' && !is_quote(quote_str[i + 1]))
			rm_quote_case_replace(&i, &j, quote_str, ret);
		else
		{
			ret[j] = quote_str[i];
			i++;
			j++;
		}
	}
}

static void	case_single_quote(int quote, int *i, int *ret_len, char *quotestr)
{

}

static void	case_not_quote(int *i, int *ret_len, char *quote_str)
{
	
}
