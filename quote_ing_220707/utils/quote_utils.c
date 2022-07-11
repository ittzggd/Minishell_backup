/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:59:14 by yukim             #+#    #+#             */
/*   Updated: 2022/07/11 15:17:16 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_len_case_exit_status(int *i, int *ret_len)
{
	char	*value;
	
	value = ft_itoa(g_data.exit_status);
	*ret_len = *ret_len + ft_strlen(value);
	*i = *i + 2;
	free(value);
}

void	get_len_case_replace_env(int *i, int *ret_len, char *quote_str)
{
	char	*key;
	char	*value;
	int		key_len;
	
	(*i)++;
	if (!ft_is_alpha(quote_str[*i]))
		key_len = 1;
	else
		key_len = ft_key_len(quote_str, *i);
	key = ft_calloc(key_len + 1, sizeof(char));
	if (!key)
		ft_error("get_len_without_quote : allocation failed\n");
	ft_strlcpy(key, &quote_str[*i], key_len + 1);
	value = get_envv(key);
	if (!value)
		value = ft_strdup("");
	*i = *i + key_len;
	*ret_len = *ret_len + ft_strlen(value);
	free(key);
	free(value);
}

void	rm_quote_case_exit_status(int *i, int *j, char *ret)
{
	char	*value;
	
	value = ft_itoa(g_data.exit_status);
	ft_strlcpy(&ret[*j], value, ft_strlen(value) + 1);
	*j = *j + ft_strlen(value);
	*i = *i + 2;
	free(value);
}

void	rm_quote_case_replace(int *i, int *j, char *quote_str, char *ret)
{
	char	*key;
	char	*value;
	int		key_len;
	
	(*i)++;
	if (!ft_is_alpha(quote_str[*i]))
		key_len = 1;
	else
		key_len = ft_key_len(quote_str, *i);
	key = ft_calloc(key_len + 1, sizeof(char));
	if (!key)
		ft_error("rm_quote_case_replace_env : allocation failed\n");
	ft_strlcpy(key, &quote_str[*i], key_len + 1);
	value = get_envv(key);
	if (!value)
		value = ft_strdup("");
	ft_strlcpy(&ret[*j], value, ft_strlen(value) + 1);
	*i = *i + key_len;
	*j = *j + ft_strlen(value);
	free(key);
	free(value);
}
