/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 14:15:15 by yukim             #+#    #+#             */
/*   Updated: 2022/06/10 14:06:04 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_envv_node	*ft_lstnew(t_envv_node element)
{
	t_envv_node	*new;

	new = (t_envv_node *)ft_calloc(1, sizeof(t_envv_node));
	if (!new)
		return (NULL);
	new->key = ft_strdup(element.key);
	if(!new->key)
		return (NULL);
	new->value = ft_strdup(element.value);
	if (!new->value)
	{
		free(new->key);
		return (NULL);
	}
	return (new);
}

void	ft_lstadd_back(t_data *data, t_envv_node *new)
{
	t_envv_node	*curr;

	curr = data->envv_list;
	if (!new)
		return ;
	if (!curr)
		curr = new;
	else
	{
		while(curr->p_link)
			curr = curr->p_link;
		curr->p_link = new;
	}
}

void	remove_ll_element(t_envv_node *p_list, char *key)
{
	t_envv_node	*curr;
	t_envv_node	*prev;

	curr = p_list;
	while (curr)
	{
		prev = curr;
		if(curr->key == key)
		{
			prev->p_link = curr->p_link;
			free(curr->value);
			free(curr->key);
			free(curr);
			return ;
		}
		curr = curr->p_link;
	}
	return ;
}





