/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_nanoshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:13:42 by hejang            #+#    #+#             */
/*   Updated: 2022/06/20 12:55:30 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*envv_join(char *key, char *value);
static char	**envvlist_to_envp(void);

void	ft_nanoshell(void)
{
	char	filepath[12];
	char	**envp;
	char	*argv[2]; 
	
	data.exit_status = 0;
	ft_strlcpy(filepath, "./nanoshell", 12);
	envp = envvlist_to_envp();
	if (!envp)
	{
		data.exit_status = 1;
		return ;
	}
	argv[0] = "./nanoshell";
	argv[1] = NULL;
	execve(filepath, argv, envp);
	// SHLVL 증가, 감소 기능 추가할지 고민
}


static char	**envvlist_to_envp(void)
{
	int			cnt;
	int			i;
	char		**envp;
	t_envv_node	*curr;

	cnt = data.envv_cnt;
	envp = (char **)ft_calloc((cnt + 1), sizeof(char *)); // malloc 후 null 체크 해주는 함수 만들기 exit
	if (!envp)
		return (NULL);
	curr = data.envv_list;
	i = 0;
	while (curr)
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
	if (value && *value)
		len2++; // =  추가
	new_str = (char *)ft_calloc(((len1 + len2) + 1), sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, key, len1 + 1);
	if (value && *value)
	{
		*(new_str + len1) = '=';
		ft_strlcat(new_str + len1 + 1, value, len2 + 1);
	}
	return (new_str);
}
