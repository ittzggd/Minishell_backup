/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:26:28 by yukim             #+#    #+#             */
/*   Updated: 2022/06/05 15:49:53 by hejang           ###   ########.fr       */
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
			printf("declare -x %s=\"%s\"\n", curr->key, curr->value);
			curr = curr->p_link;
		}
		return (0); // exit_status : 성공
	}
	while (curr)
	{
		printf("%s=%s\n", curr->key, curr->value);
		curr = curr->p_link;
	}
	return (0); // exit_status : 성공
}
