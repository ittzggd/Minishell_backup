/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 03:15:19 by hejang            #+#    #+#             */
/*   Updated: 2022/06/30 06:31:54 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include"./include/minishell.h"

static	int	get_len_without_quote(char *quote_str);

char	*remove_quote(char *quote_str)
{
	char	*ret;
	int		ret_len;
	int		i;

	i = 0;
	ret_len = get_len_without_quote(quote_str);
	if (ret_len == ft_strlen(quote_str))
		return (quote_str);
	calloc_nullcheck(&ret, ret_len + 1, sizeof(char));
	while (*quote_str)
	{
		if (!is_quote(*quote_str))
		{
			ret[i] = *quote_str;
			i++;
		}
		quote_str++;
	}
	ret[i] = '\0';
	return (ret);
}

static	int	get_len_without_quote(char *quote_str)
{
	int	i;
	int	ret_len;

	i = 0;
	ret_len = 0;
	while (quote_str[i])
	{
		if (!is_quote(quote_str[i]))
			ret_len++;
		i++;
	}
	return (ret_len);
}
