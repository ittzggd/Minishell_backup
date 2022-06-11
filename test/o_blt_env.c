/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:28 by yukim             #+#    #+#             */
/*   Updated: 2022/06/11 16:44:50 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

int	ft_env(t_data *data, int export_flag)
{
	t_envv_node *curr;

	curr = data->envv_list;
	if (export_flag == TRUE)
	{
		// 아스키코드 순 정렬
		while(curr)
		{
			if (curr->init_flag)
				printf("declare -x %s=\"%s\"\n", curr->key, curr->value);
			else
				printf("declare -x %s\n", curr->key);
			curr = curr->p_link;
		}
		return (0); // exit_status : 성공
	}
	while (curr)
	{
		if (curr->init_flag)
			printf("%s=%s\n", curr->key, curr->value);
		curr = curr->p_link;
	}
	return (0); // exit_status : 성공
}
