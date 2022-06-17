/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 14:15:15 by yukim             #+#    #+#             */
/*   Updated: 2022/06/15 19:01:25 by hejang           ###   ########.fr       */
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
	new->init_flag = element.init_flag;
	if (!new->value)
	{
		free(new->key);
		return (NULL);
	}
	return (new);
}

void	ft_lstadd_back(t_envv_node *new)
{
	t_envv_node	*curr;

	curr = data.envv_list;
	if (!new)
		return ;
	if (!curr)
		data.envv_list = new;
	else
	{
		while(curr->p_link)
			curr = curr->p_link;
		curr->p_link = new;
	}
}

void	remove_ll_element(t_envv_node **p_list, char *key)
{
	t_envv_node **tmp;
	t_envv_node	*curr;
	t_envv_node	*prev;

	tmp = p_list;
	curr = *p_list;
	prev = NULL;
	while (curr)
	{
		if (curr->key == key)
		{
			if (prev == NULL)
				tmp = &curr->p_link;
			else
				prev->p_link = curr->p_link;
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
		prev = curr;
		curr = curr->p_link;
	}
	return ;
}


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

