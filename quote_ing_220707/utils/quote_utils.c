/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 03:15:19 by hejang            #+#    #+#             */
/*   Updated: 2022/07/08 19:10:51 by hejang           ###   ########.fr       */
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
	ret = ft_calloc(ret_len + 1, sizeof(char));
	if (!ret)
		ft_error("remove_quote : allocation failed\n");
	while (quote_str[i])
	{
		quote = is_quote(quote_str[i]);
		if (quote_str[i] && quote == DOUBLE_QUOTE)
		{
			i++;
			while (quote_str[i] && quote != is_quote(quote_str[i]))
			{
				if (quote_str[i] == '$' && quote_str[i + 1] == '?')
				{
					value = ft_itoa(g_data.exit_status);
					ft_strlcpy(&ret[j], value, ft_strlen(value) + 1);
					j = j + ft_strlen(value);
					i = i + 2;
					free(value);
				}
				else if (quote_str[i] == '$' && !is_quote(quote_str[i + 1]))
				{
					i++;
					if (!ft_is_alpha(quote_str[i]))
						key_len = 1;
					else
						key_len = ft_key_len(quote_str, i);
					key = ft_calloc(key_len + 1, sizeof(char));
					if (!key)
						ft_error("remove_quote_while_1 : allocation failed\n");
					ft_strlcpy(key, &quote_str[i], key_len + 1);
					value = get_envv(key);
					if (!value)
						value = ft_strdup("");
					ft_strlcpy(&ret[j], value, ft_strlen(value) + 1);
					i = i + key_len;
					j = j + ft_strlen(value);
					free(key);
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
			{
				value = ft_itoa(g_data.exit_status);
				ft_strlcpy(&ret[j], value, ft_strlen(value) + 1);
				j = j + ft_strlen(value);
				i = i + 2;
				free(value);
			}
			else if (quote_str[i] == '$' && quote_str[i + 1] != '\0')
			{
				i++;
				if (!ft_is_alpha(quote_str[i]))
					key_len = 1;
				else
					key_len = ft_key_len(quote_str, i);
				key = ft_calloc(key_len + 1, sizeof(char));
				if (!key)
					ft_error("remove_quote_while_2 : allocation failed\n");
				ft_strlcpy(key, &quote_str[i], key_len + 1);
				value = get_envv(key);
				if (!value)
					value = ft_strdup("");
				ft_strlcpy(&ret[j], value, ft_strlen(value) + 1);
				i = i + key_len;
				j = j + ft_strlen(value);
				free(key);
				free(value);
			}
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

static	int	get_len_without_quote(char *quote_str)
{
	int	i;
	int	ret_len;
	int	quote;

	char	*key;
	char	*value;
	int		key_len;

	if (!quote_str)
		return (0);
	i = 0;
	ret_len = 0;
	while (quote_str[i])
	{
		quote = is_quote(quote_str[i]);
		if (quote_str[i] && quote == DOUBLE_QUOTE)
		{
			i++;
			while (quote_str[i] && quote != is_quote(quote_str[i]))
			{
				if (quote_str[i] == '$' && quote_str[i + 1] == '?')
				{
					value = ft_itoa(g_data.exit_status);
					ret_len = ret_len + ft_strlen(value);
					i = i + 2;
					free(value);
				}
				else if (quote_str[i] == '$' && !is_quote(quote_str[i + 1]))
				{
					i++;
					if (!ft_is_alpha(quote_str[i]))
						key_len = 1;
					else
						key_len = ft_key_len(quote_str, i);
					key = ft_calloc(key_len + 1, sizeof(char));
					if (!key)
						ft_error("get_len_without_quote : allocation failed\n");
					ft_strlcpy(key, &quote_str[i], key_len + 1);
					value = get_envv(key);
					if (!value)
						value = ft_strdup("");
					i = i + key_len;
					ret_len = ret_len + ft_strlen(value);
					free(key);
					free(value);
				}
				else
				{
					i++;
					ret_len++;
				}
			}
		}
		else if (quote_str[i] && quote == SINGLE_QUOTE)
		{
			i++;
			while (quote_str[i] && quote != is_quote(quote_str[i]))
			{
				i++;
				ret_len++;
			}
		}
		else if (quote_str[i] && quote == FALSE)
		{
			if (quote_str[i] == '$' && quote_str[i + 1] == '?')
			{
				value = ft_itoa(g_data.exit_status);
				ret_len = ret_len + ft_strlen(value);
				i = i + 2;
				free(value);
			}
			else if (quote_str[i] == '$' && quote_str[i + 1] != '\0')
			{
				i++;
				if (!ft_is_alpha(quote_str[i]))
					key_len = 1;
				else
					key_len = ft_key_len(quote_str, i);
				key = ft_calloc(key_len + 1, sizeof(char));
				if (!key)
					ft_error("get_len_without_quote : allocation failed\n");
				ft_strlcpy(key, &quote_str[i], key_len + 1);
				value = get_envv(key);
				if (!value)
					value = ft_strdup("");
				i = i + key_len;
				ret_len = ret_len + ft_strlen(value);
				free(key);
				free(value);
			}
			else
			{
				i++;
				ret_len++;
			}
			continue ;
		}
		i++;
	}
	return (ret_len);
}

/*
열린 따옴표 만나면, 같은 닫힌 따옴표 만날때 까지 하나로 퉁치고,
짝 맞는 따옴표는 제거
1. 싱글쿼트 내부 = 무조건 그냥 문자열
2. 더블쿼트 내부 = 환경변수가 있다면 치환
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
