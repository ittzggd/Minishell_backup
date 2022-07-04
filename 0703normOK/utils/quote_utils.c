/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 03:15:19 by hejang            #+#    #+#             */
/*   Updated: 2022/07/04 14:28:56 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	int	get_len_without_quote(char *quote_str);

char	*remove_quote(char *quote_str)
{
	char	*ret;
	size_t	ret_len;
	int		i;

	i = 0;
	ret_len = get_len_without_quote(quote_str);
	if (ret_len == ft_strlen(quote_str))
	{
		ret = ft_strdup(quote_str);
		return (ret);
	}
	ret = ft_calloc(ret_len + 1, sizeof(char));
	if (!ret)
		ft_error("remove_quote : allocation failed\n");
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
	if (!quote_str)
		return (0);
	while (quote_str[i])
	{
		if (!is_quote(quote_str[i]))
			ret_len++;
		i++;
	}
	return (ret_len);
}
