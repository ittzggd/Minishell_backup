/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 20:08:48 by yukim             #+#    #+#             */
/*   Updated: 2022/07/12 16:34:07 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	init_data_stdfd(t_data *data);
static void	init_data_termios(t_data *data);
static void	init_data_envvlist(t_data *data, char **envp);
static void	init_current_path(t_data *data);

void	init_setting(t_data *data, char **envp)
{
	init_data_stdfd(data);
	init_data_termios(data);
	init_current_path(data);
	init_data_envvlist(envp);
}

static void	init_data_stdfd(t_data *data)
{
	if (pipe(data->std_fd) < 0)
	{
		g_exit_status = 1;
		exit(g_exit_status);
	}
	close(data->std_fd[0]);
	close(data->std_fd[1]);
	data->std_fd[0] = dup(STDIN_FILENO);
	data->std_fd[1] = dup(STDOUT_FILENO);
}

static void	init_data_termios(t_data *data)
{
	tcgetattr(data->std_fd[0], &(data->origin_term));
	data->changed_term = data->origin_term;
	data->changed_term.c_lflag &= ~(ECHOCTL);
	tcsetattr(data->std_fd[0], TCSANOW, &(data->changed_term));
}

static void	init_data_envvlist(t_data *data, char **envp)
{
	char	*key;
	char	*value;

	while (*envp)
	{
		init_envp(data, *envp, &key, &value);
		insert_envv(data, key, value, TRUE);
		envp++;
	}
}

static void	init_current_path(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	data->current_path = cwd;
}
