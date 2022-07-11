/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:36:07 by yukim             #+#    #+#             */
/*   Updated: 2022/07/11 19:11:21 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	get_changed_str(int i, int j, char **ret, char *quote_str);
static void	copy_char(char *quote_str, int *i, int *j, char *ret);
static void	case_double_quote(char *quote_str, int *i, int *j, char *ret);
static void	case_not_quote(char *quote_str, int *i, int *j, char *ret);

char	*remove_quote(char *quote_str)
{
	char	*ret;
	size_t	ret_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret_len = get_len_without_quote(quote_str);
	ret = ft_calloc(ret_len + 1, sizeof(char));
	if (!ret)
		ft_error("remove_quote : allocation failed\n");
	get_changed_str(i, j, &ret, quote_str);
	return (ret);
}

static void	get_changed_str(int i, int j, char **ret, char *quote_str)
{
	int	quote;

	while (quote_str[i])
	{
		quote = is_quote(quote_str[i]);
		if (quote_str[i] && quote == DOUBLE_QUOTE)
		{
			i++;
			while (quote_str[i] && quote != is_quote(quote_str[i]))
				case_double_quote(quote_str, &i, &j, *ret);
		}
		else if (quote_str[i] && quote == SINGLE_QUOTE)
		{
			i++;
			while (quote_str[i] && quote != is_quote(quote_str[i]))
				copy_char(quote_str, &i, &j, *ret);
		}
		else if (quote_str[i] && quote == FALSE)
		{
			case_not_quote(quote_str, &i, &j, *ret);
			continue ;
		}
		i++;
	}
	(*ret)[j] = '\0';
}

static void	copy_char(char *quote_str, int *i, int *j, char *ret)
{
	ret[*j] = quote_str[*i];
	(*i)++;
	(*j)++;
}

static void	case_double_quote(char *quote_str, int *i, int *j, char *ret)
{
	if (quote_str[*i] == '$' && quote_str[*i + 1] == '?')
		rm_quote_case_exit_status(i, j, ret);
	else if (quote_str[*i] == '$' && !is_quote(quote_str[*i + 1]))
		rm_quote_case_replace(i, j, quote_str, ret);
	else
		copy_char(quote_str, i, j, ret);
}

static void	case_not_quote(char *quote_str, int *i, int *j, char *ret)
{
	if (quote_str[*i] == '$' && quote_str[*i + 1] == '?')
		rm_quote_case_exit_status(i, j, ret);
	else if (quote_str[*i] == '$' && quote_str[*i + 1] != '\0')
		rm_quote_case_replace(i, j, quote_str, ret);
	else
		copy_char(quote_str, i, j, ret);
}
