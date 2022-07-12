/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_nanoshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:13:42 by hejang            #+#    #+#             */
/*   Updated: 2022/07/12 19:19:05 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_nanoshell(t_data *data, char *filepath)
{
	char		**envp;
	char		*argv[2];
	struct stat	*buf;

	buf = NULL;
	reset_stdfd();
	g_exit_status = 0;
	if (ft_strncmp(filepath, "minishell", -1) && stat(filepath, buf) == -1)
	{
		ft_error_message("minishell : command not found : ", 1);
		ft_error_message(filepath, 1);
		ft_error_message("\n", 1);
		exit(g_exit_status);
	}
	envp = envvlist_to_envp();
	argv[0] = "./minishell";
	argv[1] = NULL;
	execve(argv[0], argv, envp);
}

char	**envvlist_to_envp(void)
{
	int			cnt;
	int			i;
	char		**envp;
	t_envv_node	*curr;

	cnt = data.envv_cnt;
	envp = (char **)ft_calloc((cnt + 1), sizeof(char *));
	if (!envp)
		ft_error("envvlist_to_envp : alloction failed\n");
	curr = data.envv_list;
	i = 0;
	while (curr)
	{
		envp[i] = envv_join(curr->key, curr->value);
		i++;
		curr = curr->p_link;
	}
	envp[i] = NULL;
	return (envp);
}

char	*envv_join(char *key, char *value)
{
	size_t	len1;
	size_t	len2;
	char	*new_str;

	if (!key)
		return (NULL);
	len1 = ft_strlen(key);
	len2 = ft_strlen(value);
	if (value && *value)
		len2++;
	new_str = ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!new_str)
		ft_error("envv_join : allocation failed\n");
	ft_strlcpy(new_str, key, len1 + 1);
	if (value && *value)
	{
		*(new_str + len1) = '=';
		ft_strlcat(new_str + len1 + 1, value, len2 + 1);
	}
	return (new_str);
}
