/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_02.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:05:45 by hejang            #+#    #+#             */
/*   Updated: 2022/07/11 15:19:05 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	heredoc_replace_loop(char *origin)
{
	while (origin[i])
	{
		quote = is_quote(origin[i + 1]);
		if (origin[i] == '$' && origin[i + 1] == '?')
		{
			value = ft_itoa(g_data.exit_status);
			ft_strlcpy(&ret[j], value, ft_strlen(value) + 1);
			j = j + ft_strlen(value);
			i = i + 2;
		}
		else if (origin[i] == '$' && origin[i + 1] != '\0' && quote == 0)
			heredoc_replace_env(origin, ret, &i, &j);
		else
		{
			ret[j] = origin[i];
			i++;
			j++;
		}
	}
}

void	heredoc_replace_env(char *origin, char *ret, int *i, int *j)
{
	int		key_len;
	char	*key;
	char	*value;
	
	(*i)++;
	if (!ft_is_alpha(origin[*i]))
		key_len = 1;
	else
		key_len = ft_key_len(origin, *i);
	key = ft_calloc(key_len + 1, sizeof(char));
	if (!key)
		ft_error("replace_env_in_heredoc : allocation failed\n");
	ft_strlcpy(key, &origin[*i], key_len + 1);
	value = get_envv(key);
	if (!value)
		value = ft_strdup("");
	ft_strlcpy(&ret[*j], value, ft_strlen(value) + 1);
	i = i + key_len;
	j = j + ft_strlen(value);
	free(key);
	free(value);
	return (key_len);
}

