/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 09:59:43 by hejang            #+#    #+#             */
/*   Updated: 2022/07/02 21:05:34 by hejang           ###   ########.fr       */
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
	if (check_env(token, i, &j) == TRUE)
		return ;
	key_len = 0;
	while (token[j + key_len])
	{
		if (!ft_is_alpha(token[j + key_len]) && (token[j + key_len] != '_') \
				&& !ft_is_digit(token[j + key_len]) && (token[j + key_len] != '?'))
			break ;
		key_len++;
	}
	key = ft_calloc(key_len + 1, sizeof(char));
	if (!key)
		ft_error("replace_env_to_value : allocation failed\n");
	if (key)
		get_value(key, token, key_len, i, j);
}

void	insert_envv(char *key, char *value, int init_flag)
{
	t_envv_node	element;
	t_envv_node	*is_exist;
	t_envv_node	*new;
	char		*tmp;

	is_exist = get_el_node(data.envv_list, key);
	if (is_exist)
	{
		tmp = is_exist->value;
		is_exist->value = ft_strdup(value);
		free(value);
		free(tmp);
	}
	else
	{
		element.key = key;
		element.value = value;
		element.init_flag = init_flag;
		new = ft_lstnew(element);
		ft_lstadd_back(new);
		free(key);
		free(value);
		data.envv_cnt++;
	}
}

char	*get_envv(char *key)
{
	t_envv_node	*key_node;
	char		*ret;

	key_node = get_el_node(data.envv_list, key);
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
	int		i;
	int		init_flag;
	char	*p_equal;

	p_equal = ft_strchr(input, '=');
	if (p_equal)
	{
		init_flag = TRUE;
		*key = ft_calloc(p_equal - input + 1, sizeof(char));
		if(!*key)
			ft_error("init_envp : allocation failed");
		ft_strlcpy(*key, input, p_equal - input + 1);
		*value = ft_strdup(p_equal + 1);
		if(!(*value))
			return (ERROR);	
}
	else
	{
		*key = ft_strdup(input);
		*value = NULL;
	}
	return (init_flag);
}
