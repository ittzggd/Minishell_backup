/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 20:08:48 by yukim             #+#    #+#             */
/*   Updated: 2022/07/03 17:31:53 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	init_data_stdfd(void);
static void	init_data_termios(void);
static void	init_data_envvlist(char **envp);

void	init_setting(char **envp)
{
	init_data_stdfd();
	init_data_termios();
	init_data_envvlist(envp);
}

static void	init_data_stdfd(void)
{
	if (pipe(g_data.std_fd) < 0)
	{
		g_data.exit_status = 1;
		exit(g_data.exit_status);
	}
	close(g_data.std_fd[0]);
	close(g_data.std_fd[1]);
	g_data.std_fd[0] = dup(STDIN_FILENO);
	g_data.std_fd[1] = dup(STDOUT_FILENO);
}

static void	init_data_termios(void)
{
	tcgetattr(g_data.std_fd[0], &g_data.origin_term);
	g_data.changed_term = g_data.origin_term;
	g_data.changed_term.c_lflag &= ~(ECHOCTL);
	tcsetattr(g_data.std_fd[0], TCSANOW, &g_data.changed_term);
}

static void	init_data_envvlist(char **envp)
{
	char	*key;
	char	*value;

	while (*envp)
	{
		init_envp(*envp, &key, &value);
		insert_envv(key, value, TRUE);
		envp++;
	}
}
