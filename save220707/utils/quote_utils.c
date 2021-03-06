/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 03:15:19 by hejang            #+#    #+#             */
/*   Updated: 2022/07/04 19:23:334 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	int	get_len_without_quote(char *quote_str);

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
	if (ret_len == ft_strlen(quote_str))
	{
		ret = ft_strdup(quote_str);
		return (ret);
	}
	ret = ft_calloc(ret_len + 1, sizeof(char));
	if (!ret)
		ft_error("remove_quote : allocation failed\n");
	while (quote_str[i])
	{
		quote = is_quote(quote_str[i]);
		if (quote_str[i] && quote)
		{
			i++;
			while (quote_str[i] && quote != is_quote(quote_str[i]))
			{
				if (quote == DOUBLE_QUOTE && quote_str[i] == '$')
				{
					i++;
					key_len = ft_key_len(quote_str, i);
					key = ft_calloc(key_len + 1, sizeof(char));
					if (!key)
						ft_error("get_len_without_quote : allocation failed\n");
					ft_strlcpy(key, &quote_str[i], key_len + 1);
					value = get_envv(key);
					ft_strlcpy(&ret[j], value, ft_strlen(value) + 1);
					i = i + key_len;
					if (key)
						free(key);
					if (!value)
						value = ft_strdup("");
					j = j + ft_strlen(value);
					if (value)
						free(value);
				}
				else
				{
					ret[j] = quote_str[i];
					i++;
					j++;
				}
			}
		}
		else if (quote_str[i])
		{
			ret[j] = quote_str[i];
			j++;
		}
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

static	int	get_len_without_quote(char *quote_str)
{
	int	i;
	int	len;
	int	quote;

	char	*key;
	char	*value;
	int		key_len;

	if (!quote_str)
		return (0);
	i = 0;
	len = 0;
	while (quote_str[i])
	{
		quote = is_quote(quote_str[i]);
		if (quote_str[i] && quote)
		{

		}
		else
		{
			len++;
		}
		i++;
	}
	return (len);
}






/*
?????? ????????? ?????????, ?????? ?????? ????????? ????????? ?????? ????????? ?????????,
??? ?????? ???????????? ??????
1. ???????????? ?????? = ????????? ?????? ?????????
2. ???????????? ?????? = ??????????????? ????????? ??????
*/

// char	*remove_quote(char *quote_str)
// {
// 	char	*ret;
// 	size_t	ret_len;
// 	int		quote;
// 	int		i;
// 	int		j;

// 	char	*key;
// 	char	*value;
// 	int		key_len;

// 	i = 0;
// 	j = 0;
// 	ret_len = get_len_without_quote(quote_str);
// 	if (ret_len == ft_strlen(quote_str))
// 	{
// 		ret = ft_strdup(quote_str);
// 		return (ret);
// 	}
// 	ret = ft_calloc(ret_len + 1, sizeof(char));
// 	if (!ret)
// 		ft_error("remove_quote : allocation failed\n");
// 	while (quote_str[i])
// 	{
// 		quote = is_quote(quote_str[i]);
// 		if (quote_str[i] && quote)
// 		{
// 			i++;
// 			while (quote_str[i] && quote != is_quote(quote_str[i]))
// 			{
// 				if (quote == DOUBLE_QUOTE && quote_str[i] == '$')
// 				{
// 					i++;
// 					key_len = ft_key_len(quote_str, i);
// 					key = ft_calloc(key_len + 1, sizeof(char));
// 					if (!key)
// 						ft_error("get_len_without_quote : allocation failed\n");
// 					ft_strlcpy(key, &quote_str[i], key_len + 1);
// 					value = get_envv(key);
// 					ft_strlcpy(&ret[j], value, ft_strlen(value) + 1);
// 					i = i + key_len;
// 					if (key)
// 						free(key);
// 					if (!value)
// 						value = ft_strdup("");
// 					j = j + ft_strlen(value);
// 					if (value)
// 						free(value);
// 				}
// 				else
// 				{
// 					ret[j] = quote_str[i];
// 					i++;
// 					j++;
// 				}
// 			}
// 		}
// 		else if (quote_str[i])
// 		{
// 			ret[j] = quote_str[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	ret[j] = '\0';
// 	return (ret);
// }

// static	int	get_len_without_quote(char *quote_str)
// {
// 	int	i;
// 	int	ret_len;
// 	int	quote;

// 	char	*key;
// 	char	*value;
// 	int		key_len;

// 	if (!quote_str)
// 		return (0);
// 	i = 0;
// 	ret_len = 0;
// 	while (quote_str[i])
// 	{
// 		quote = is_quote(quote_str[i]);
// 		if (quote_str[i] && quote)
// 		{
// 			i++;
// 			while (quote_str[i] && quote != is_quote(quote_str[i]))
// 			{
// 				if (quote == DOUBLE_QUOTE && quote_str[i] == '$')
// 				{
// 					i++;
// 					key_len = ft_key_len(quote_str, i);
// 					key = ft_calloc(key_len + 1, sizeof(char));
// 					if (!key)
// 						ft_error("get_len_without_quote : allocation failed\n");
// 					ft_strlcpy(key, &quote_str[i], key_len + 1);
// 					value = get_envv(key);
// 					i = i + key_len;
// 					if (key)
// 						free(key);
// 					if (!value)
// 						value = ft_strdup("");
// 					ret_len = ret_len + ft_strlen(value);
// 					if (value)
// 						free(value);
// 				}
// 				else
// 				{
// 					i++;
// 					ret_len++;
// 				}
// 			}
// 		}
// 		else if (quote_str[i])
// 			ret_len++;
// 		i++;
// 	}
// 	return (ret_len);
// }
