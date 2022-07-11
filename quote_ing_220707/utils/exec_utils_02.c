/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:46:06 by hejang            #+#    #+#             */
/*   Updated: 2022/07/11 14:55:10 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fork_before_run_execve_child(int idx, char *execve_cmd, char **argv)
{
	char	**filepath;
	
	reset_signal();
	if (ft_strchr(execve_cmd, '/'))
	{
		filepath = ft_calloc(2, sizeof(char *));
		filepath[0] = ft_strdup(execve_cmd);
		filepath[1] = NULL;
	}
	else
		filepath = join_filepath(execve_cmd);
	if (!filepath)
		filepath = allocate_empty_str_in_filepath();
	while (filepath[idx])
	{
		if (execve(filepath[idx], argv, NULL) == -1)
			idx++;
		else
			break ;
	}
	if (!filepath[idx])
		command_not_found_error(argv[0]);
}
