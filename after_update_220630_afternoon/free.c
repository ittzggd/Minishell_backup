/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:23:54 by yukim             #+#    #+#             */
/*   Updated: 2022/07/01 17:08:25 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

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
//	free_data_envvlist();
}


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
