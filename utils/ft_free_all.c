/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:23:54 by yukim             #+#    #+#             */
/*   Updated: 2022/06/11 15:27:03 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_free_all(char **ret)
{
	int	i;

	i = 0;
	if (ret)
	{
		while (ret[i])
		{
			free(ret[i]);
			i++;
		}
		free(ret);
	}
	return (NULL);
}
