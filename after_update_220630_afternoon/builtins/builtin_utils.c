/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 04:18:16 by yukim             #+#    #+#             */
/*   Updated: 2022/07/01 11:51:14 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_pwd_oldpwd(char *key)
{
	char		*value;
	char		*tmp;
	t_envv_node	*node;

	node = get_el_node(data.envv_list, key);
	if (node)
	{
		if (ft_strncmp(key, "OLDPWD", -1))
			value = get_envv("PWD");
		else if (ft_strncmp(key, "PWD", -1))
		{
			if (node->value)
			{
				free(node->value);
				node->value = NULL;
			}
			value = getcwd(NULL, 0);
		}
		insert_envv(key, value, TRUE);
	}
}
