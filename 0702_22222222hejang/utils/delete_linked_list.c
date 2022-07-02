/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_linked_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 14:15:15 by yukim             #+#    #+#             */
/*   Updated: 2022/07/02 18:49:12 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clear_linked_list(t_envv_node **p_list)
{
	t_envv_node **tmp;
	t_envv_node	*curr;

	tmp = p_list;
	curr = *p_list;
	tmp = &curr->p_link;
	if (curr->value)
		free(curr->value);
	if (curr->key)
		free(curr->key);
	if (curr)
		free(curr);
	p_list = tmp;
	data.envv_list = *p_list;
	return ;
}

void	delete_linked_list(t_envv_node **p_list)
{
	if(!p_list || !*p_list)
		return ;
	clear_linked_list(p_list);
	free(p_list);
	p_list = NULL;
}
