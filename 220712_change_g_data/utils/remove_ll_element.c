/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_ll_element.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:47:04 by yukim             #+#    #+#             */
/*   Updated: 2022/07/12 19:23:07 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init_prev(t_envv_node **tmp, t_envv_node *curr, t_envv_node *prev);
static void	free_envv_node(t_envv_node *curr);

void	remove_ll_element(t_data *data, t_envv_node **p_list, char *key)
{
	t_envv_node	**tmp;
	t_envv_node	*curr;
	t_envv_node	*prev;

	tmp = p_list;
	curr = *p_list;
	prev = NULL;
	while (curr)
	{
		if (curr->key == key)
		{
			init_prev(tmp, curr, prev);
			free_envv_node(curr);
			p_list = tmp;
			data->envv_list = *p_list;
			return ;
		}
		prev = curr;
		curr = curr->p_link;
	}
	return ;
}

static void	free_envv_node(t_envv_node *curr)
{
	if (curr->value)
		free(curr->value);
	if (curr->key)
		free(curr->key);
	if (curr)
		free(curr);
}

static void	init_prev(t_envv_node **tmp, t_envv_node *curr, t_envv_node *prev)
{
	if (prev == NULL)
		*tmp = curr->p_link;
	else
		prev->p_link = curr->p_link;
}
