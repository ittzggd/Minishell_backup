/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 09:59:43 by hejang            #+#    #+#             */
/*   Updated: 2022/07/12 14:35:52 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	free_arg(char *key,char *value);

void	insert_envv(char *key, char *value, int init_flag)
{
	t_envv_node	element;
	t_envv_node	*is_exist;
	t_envv_node	*new;
	char		*tmp;

	is_exist = get_el_node(g_data.envv_list, key);
	if (is_exist)
	{
		if(!value)
		{
			free(key);
			return;
		}
		tmp = is_exist->value;
		is_exist->value = ft_strdup(value);
		is_exist->init_flag = TRUE;
		free_arg(key, value);
		free(tmp);
	}
	else
	{
		element.key = key;
		element.value = value;
		element.init_flag = init_flag;
		new = ft_lstnew(element);
		ft_lstadd_back(new);
		free_arg(key, value);
		g_data.envv_cnt++;
	}
}

char	*get_envv(char *key)
{
	t_envv_node	*key_node;
	char		*ret;

	key_node = get_el_node(g_data.envv_list, key);
	if (!key_node)
		return (NULL);
	ret = ft_strdup(key_node->value);
	return (ret);
}

t_envv_node	*get_el_node(t_envv_node *envv_list, char *key)
{
	t_envv_node	*curr;

	curr = envv_list;
	while (curr)
	{
		if (ft_strncmp(key, curr->key, -1))
			break ;
		curr = curr->p_link;
	}
	return (curr);
}

int	init_envp(char *input, char **key, char **value)
{
	int		init_flag;
	char	*p_equal;

	init_flag = 999;
	p_equal = ft_strchr(input, '=');
	if (p_equal)
	{
		init_flag = TRUE;
		*key = ft_calloc(p_equal - input + 1, sizeof(char));
		if (!*key)
			ft_error("init_envp : allocation failed\n");
		ft_strlcpy(*key, input, p_equal - input + 1);
		*value = ft_strdup(p_equal + 1);
		if (!(*value))
			return (ERROR);
	}
	else
	{
		init_flag = FALSE;
		*key = ft_strdup(input);
		*value = NULL;
	}
	return (init_flag);
}

static void	free_arg(char *key,char *value)
{
	free(key);
	free(value);
}
