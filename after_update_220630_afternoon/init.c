/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 20:08:48 by yukim             #+#    #+#             */
/*   Updated: 2022/06/30 04:45:54 by yukim            ###   ########seoul.kr  */
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
	if (pipe(data.std_fd) < 0)
	{
		data.exit_status = 1;
		exit(data.exit_status);
	}
	close(data.std_fd[0]);
	close(data.std_fd[1]);
	data.std_fd[0] = dup(STDIN_FILENO);
	data.std_fd[1] = dup(STDOUT_FILENO);
}

static void	init_data_termios(void)
{
	tcgetattr(data.std_fd[0], &data.origin_term);
	data.changed_term = data.origin_term;
	data.changed_term.c_lflag &= ~(ECHOCTL);
	tcsetattr(data.std_fd[0], TCSANOW, &data.changed_term);
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
	insert_envv("OLDPWD", NULL, TRUE);
}
