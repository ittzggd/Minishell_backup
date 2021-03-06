/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_blt_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:28 by yukim             #+#    #+#             */
/*   Updated: 2022/07/01 11:51:35 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

int	ft_env(int export_flag)
{
	t_envv_node	*curr;

	curr = data.envv_list;
	data.exit_status = 0;
	if (export_flag == TRUE)
	{
		while (curr)
		{
			if (curr->init_flag)
				printf("declare -x %s=\"%s\"\n", curr->key, curr->value);
			else
				printf("declare -x %s\n", curr->key);
			curr = curr->p_link;
		}
		return (data.exit_status);
	}
	while (curr)
	{
		if (curr->init_flag)
			printf("%s=%s\n", curr->key, curr->value);
		curr = curr->p_link;
	}
	return (data.exit_status);
}
