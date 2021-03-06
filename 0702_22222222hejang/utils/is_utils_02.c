/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils_02.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:44:39 by katherineja       #+#    #+#             */
/*   Updated: 2022/07/02 18:53:01 by hejang           ###   ########.fr       */
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

	i = 0;
	if (value[i] == '$' || (value[i] == '\"' && value[i + 1] == '$'))
		return (TRUE);
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
