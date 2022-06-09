/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_itoa.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:23:40 by yukim             #+#    #+#             */
/*   Updated: 2022/06/09 12:50:21 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t	ft_numlen(size_t num)
{
	size_t	len;

	if (num == 0)
		return (1);
	len = 0;
	while (num)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(size_t num)
{
	char	*new;
	size_t		len;
	int		i;

	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	len = ft_numlen(num);
	i = len;
	while (i > -1)
	{
		if ((size_t)i == len)
			new[i] = '\0';
		else
		{
			new[i] = (num % 10) + '0';
			num = num / 10;
		}
		i--;
	}
	return (new);
}
