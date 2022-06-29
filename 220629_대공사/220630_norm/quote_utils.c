/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 03:15:19 by hejang            #+#    #+#             */
/*   Updated: 2022/06/30 03:20:53 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"./include/minishell.h"

static	int	get_len_witout_quote(char *quote_str);

char	*remove_quote(char *quote_str)
{
	char	*ret;
	int		ret_len;
	int		i;

	i = 0;
	ret_len = get_len_without_quote(quote_str);
	if (ret_len == ft_strlen(quote_str))
		return (quote_str);
	ret = (char *)malloc(sizeof(char) * (ret_len + 1));
	if (!ret)
		return (NULL);
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

static	int	get_len_witout_quote(char *quote_str)
{
	int	i;

	i = 0;
	while (quote_str[i])
	{
		if (!is_quote(quote_str[i]))
			ret_len++;
		i++;
	}
	return (ret_len);
}
