/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:52:48 by hejang            #+#    #+#             */
/*   Updated: 2022/06/13 19:07:4 by yukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*envv_join(char *key, char *value);

char	**envvlist_to_envp(void)
{
	int			cnt;
	int			i;
	char		**envp;
	t_envv_node	*curr;

	cnt = 0;
	curr = data->envv_list;
	while (curr)
	{
		cnt++;
		curr = curr->p_link;
	}
	envp = (char **)malloc(sizeof(char *) * (cnt + 1)); // malloc 후 null 체크 해주는 함수 만들기 exit
	if (!envp)
		return (NULL);
	curr = data->envv_list;
	i = 0;
	while(curr)
	{
		envp[i] = envv_join(curr->key, curr->value);
		if (!envp[i])
			return (NULL); // ft_free_all
		i++;
		curr = curr->p_link;
	}
	envp[i] = NULL;
	return (envp);
}

static char	*envv_join(char *key, char *value)
{
	size_t	len1;
	size_t	len2;
	char	*new_str;

	if (!key)
		return (NULL);
	len1 = ft_strlen(key);
	len2 = ft_strlen(value);
	new_str = (char *)malloc(sizeof(char) * (len1 + len2) + 2);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, key, len1 + 1);
	if(value)
	{
		*(new_str + len1) = '=';
		ft_strlcat(new_str + len1 + 1, value, len2 + 1);
	}
	return (new_str);
}
