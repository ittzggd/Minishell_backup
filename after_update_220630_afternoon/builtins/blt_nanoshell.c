/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_nanoshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:13:42 by hejang            #+#    #+#             */
/*   Updated: 2022/06/29 23:22:13 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_nanoshell(char *filepath)
{
	char		**envp;
	char		*argv[2];
	struct stat	*buf;

	reset_stdfd();
	if (!ft_strncmp(filepath, "nanoshell", -1) && stat(filepath, buf) == -1)
	{
		ft_error_message("nanoshell : command not found : ", 1);
		ft_error_message(filepath, 1);
		ft_error_message("\n", 1);
		exit(data.exit_status);
	}
	envp = envvlist_to_envp();
	argv[0] = "./nanoshell";
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
	{
		free_all_in_data();
		exit(1);
	}
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
	calloc_nullcheck(&new_str, len1 + len2 + 1, sizeof(char));
	ft_strlcpy(new_str, key, len1 + 1);
	if (value && *value)
	{
		*(new_str + len1) = '=';
		ft_strlcat(new_str + len1 + 1, value, len2 + 1);
	}
	return (new_str);
}
