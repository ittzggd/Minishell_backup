/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils_02.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:44:39 by katherineja       #+#    #+#             */
/*   Updated: 2022/07/03 16:56:11 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_option(char *value)
{
	if (*value != '-')
		return (FALSE);
	value++;
	if (*value == '\0')
		return (FALSE);
	while (*value)
	{
		if (*value != 'n')
			return (FALSE);
		value++;
	}
	return (TRUE);
}

int	is_env(char *value)
{
	int	i;
	int	quote;

	i = 0;
	while (value[i])
	{
		quote = is_quote(value[i]);
		if (value[i] && quote)
		{
			i++;
			while (value[i] && quote != is_quote(value[i]))
			{
				if (quote == DOUBLE_QUOTE && value[i] == '$')
					return (TRUE);
				if (quote == DOUBLE_QUOTE && value[i] == '$' && is_quote(value[i + 1])== DOUBLE_QUOTE)
					return (FALSE);
				i++;
			}
		}
		else if (quote == 0 && value[i] == '$')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	is_valid_env(char *str)
{
	if (!ft_is_alpha(*str) && (*str != '_'))
		return (ERROR);
	else if (ft_strncmp(str, "_=", 2) || ft_strncmp(str, "_", ft_strlen(str)))
		return (FALSE);
	while (*str != '\0')
	{
		if (!ft_is_alpha(*str) && (*str != '_') \
				&& !ft_is_digit(*str) && (*str != '?'))
			return (ERROR);
		str++;
	}
	return (TRUE);
}

int	ft_is_alpha(char c)
{
	if ('A' <= c && c <= 'Z')
		return (1);
	else if ('a' <= c && c <= 'z')
		return (2);
	else
		return (0);
}

int	ft_is_digit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}
