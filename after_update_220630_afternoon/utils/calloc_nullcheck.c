/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc_nullcheck.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 03:33:10 by yukim             #+#    #+#             */
/*   Updated: 2022/06/30 05:31:01 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	calloc_nullcheck(void **address, int count, int size)
{
	*address = ft_calloc(count, size);
	if (!(*address))
	{
		free_all_in_data();
		exit(1);
	}
}
