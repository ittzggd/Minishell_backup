/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_nanoshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:13:42 by hejang            #+#    #+#             */
/*   Updated: 2022/06/28 18:52:10 by yukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"



void	ft_nanoshell(char *filepath)
{
	// pid_t		pid;
	char		**envp;
	char		*argv[2];
	struct stat	*buf;
	
	// data->exit_status = 0;
	// pid = fork();
	// if (pid < 0)
	// {
	// 	exit(1);
	// }
	// if(pid == 0)	
	// {
		dup2(data->std_fd[0], STDIN_FILENO);
		dup2(data->std_fd[1], STDOUT_FILENO);
		
		if (!ft_strncmp(filepath, "nanoshell", -1) && stat(filepath, buf) == -1)
		{
			printf("nanoshell : command not found : %s\n", filepath);
			data->exit_status = 1;
			exit(data->exit_status);
		}
		envp = envvlist_to_envp();
		if (!envp)
		{
			data->exit_status = 1;
			return ;
		}
		argv[0] = "./nanoshell";
		argv[1] = NULL;
		execve(argv[0], argv, envp);
		// SHLVL 증가, 감소 기능 추가할지 고민
		// 부모 미니쉘은 시그널 끄기
	// }
	// else
	// 	waitpid(pid, &data->exit_status, 0);
}


char	**envvlist_to_envp(void)
{
	int			cnt;
	int			i;
	char		**envp;
	t_envv_node	*curr;

	cnt = data->envv_cnt;
	envp = (char **)ft_calloc((cnt + 1), sizeof(char *)); // malloc 후 null 체크 해주는 함수 만들기 exit
	if (!envp)
		return (NULL);
	curr = data->envv_list;
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
