/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils_02.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:44:39 by katherineja       #+#    #+#             */
/*   Updated: 2022/06/04 20:37:28 by hejang           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_option(char *value)
{
	if (*value != '-')
		return (FALSE);
	value++;
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

	i = 0;
	if (value[i] == '$' || (value[i] == '\"' && value[i + 1] == '$'))
		return (is_valid_env(value));
	return (FALSE);
}

int	is_valid_env(char *str)
{
	if (*str != '$')
		return (FALSE);
	str++;
	if (!ft_is_alpha(*str) && (*str != '_'))
		return (FALSE);
	while (*str != '\0')
	{
		if (!ft_is_alpha(*str) && (*str != '_') \
				&& !ft_is_digit(*str) && (*str != '?'))
			return (FALSE);
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
