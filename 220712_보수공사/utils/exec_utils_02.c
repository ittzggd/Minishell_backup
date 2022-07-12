/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:46:06 by hejang            #+#    #+#             */
/*   Updated: 2022/07/12 14:35:52 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fork_before_run_execve_child(int idx, char *ecve_cmd, char **argv)
{
	char	**filepath;
	char	**envp;

	reset_signal();
	envp = envvlist_to_envp();
	if (ft_strchr(ecve_cmd, '/'))
	{
		filepath = ft_calloc(2, sizeof(char *));
		filepath[0] = ft_strdup(ecve_cmd);
		filepath[1] = NULL;
	}
	else
		filepath = join_filepath(ecve_cmd);
	if (!filepath)
		filepath = allocate_empty_str_in_filepath();
	while (filepath[idx])
	{
		if (execve(filepath[idx], argv, envp) == -1)
			idx++;
		else
			break ;
	}
	if (!filepath[idx])
		command_not_found_error(argv[0]);
}
