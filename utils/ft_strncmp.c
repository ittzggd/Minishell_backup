/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katherinejang <katherinejang@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:46:30 by yukim             #+#    #+#             */
/*   Updated: 2022/05/28 10:34:26 by katherineja      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (TRUE);
		if (s1[i] != s2[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}