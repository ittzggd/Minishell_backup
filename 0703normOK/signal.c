/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:36:12 by yukim             #+#    #+#             */
/*   Updated: 2022/06/29 23:36:0 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	ft_sig_handler_in_heredoc(int sig_num)
{
	if (sig_num == SIGINT)
	{
		close(STDIN_FILENO);
		ft_error_message("\n", 1);
		rl_on_new_line();
		g_data.exit_status = 1;
		if (g_data.p_flag == TRUE)
			exit(g_data.exit_status);
	}
	else if (sig_num == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ctrl_c(int sig_num)
{
	(void)sig_num;
	if (g_data.heredoc_flag == TRUE)
		return ;
	if (g_data.p_flag == TRUE)
	{
		ft_error_message("", 130);
		rl_on_new_line();
		exit(g_data.exit_status);
	}
	else if (g_data.p_flag == FALSE)
	{
		ft_error_message("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ctrl_bs(int sig_num)
{
	(void)sig_num;
	if (g_data.p_flag == TRUE)
	{
		if (g_data.heredoc_flag == TRUE)
			return ;
		ft_error_message("Quit: 3\n", 131);
		exit(g_data.exit_status);
	}
	else if (g_data.p_flag == FALSE)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}
