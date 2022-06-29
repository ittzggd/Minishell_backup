/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc_nullcheck.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 03:33:10 by yukim             #+#    #+#             */
/*   Updated: 2022/06/30 04:16:35 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	calloc_nullcheck(void **address, int count, int size)
{
	*address = ft_calloc(count, size);
	if (!(*address))
	{
		free_all_in_data();
		exit(1);
	}
}

void	free_data_envvlist(void)
{
	t_envv_node	*curr;
	t_envv_node	*del;

	if (!data.envv_list)
		return ;
	curr = data.envv_list;
	while (curr)
	{
		del = curr;
		curr = curr->p_link;
		if (del->key)
			free(del->key);
		if (del->value)
			free(del->value);
		free(del);
	}
	data.envv_list = NULL;
}

void	free_all_in_data(void)
{
	reset_data();
	free_data_envvlist();
}
