/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 09:59:43 by hejang            #+#    #+#             */
/*   Updated: 2022/06/30 05:29:45 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	replace_env_to_value(int i)
{
	char	*key;
	char	*token;
	char	*argv;
	int		j;
	int		key_len;

	token = data.lexer.pptokens[i];
	j = 0;
	if (check_env(token, i, j) == TRUE)
		return ;
	while (token[j] && (token[j] == '$'
			|| (token[j] == '\"' && token[j + 1] == '$')))
		j++;
	key_len = 0;
	while (token[j + key_len] && token[j + key_len] != '\"')
		key_len++;
	key = (char *)malloc(key_len + 1);
	if (key)
	{
		get_value(key, token, key_len, i, j);
	}
}

void	insert_envv(char *key, char *value, int init_flag)
{
	t_envv_node	element;
	t_envv_node	*is_exist;
	t_envv_node	*new;

	is_exist = get_el_node(data.envv_list, key);
	if (is_exist)
	{
		if (is_exist->value)
			free(is_exist->value);
		is_exist->value = ft_strdup(value);
	}
	else
	{
		element.key = key;
		element.value = value;
		element.init_flag = init_flag;
		new = ft_lstnew(element);
		ft_lstadd_back(new);
		data.envv_cnt++;
	}
}

char	*get_envv(char *key)
{
	t_envv_node	*key_node;

	key_node = get_el_node(data.envv_list, key);
	if (!key_node)
		return (NULL);
	return (key_node->value);
}

t_envv_node	*get_el_node(t_envv_node *envv_list, char *key)
{
	t_envv_node	*curr;

	curr = envv_list;
	while (curr)
	{
		if (ft_strncmp(key, curr->key, ft_strlen(key)))
			break ;
		curr = curr->p_link;
	}
	return (curr);
}

int	init_envp(char *input, char **key, char **value)
{
	int		i;
	int		init_flag;
	char	*p_equal;

	init_flag = FALSE; // 220701 added : maybe NUll is user init? or auto setting? distinguish
	p_equal = ft_strchr(input, '=');
	if (p_equal)
	{
		init_flag = TRUE;
		calloc_nullcheck((void **)key, p_equal - input + 1, sizeof(char));
		ft_strlcpy(*key, input, p_equal - input + 1);
		*value = ft_strdup(p_equal + 1);
	}
	else
	{
		*key = input;
		*value = NULL;
	}
	return (init_flag);
}
