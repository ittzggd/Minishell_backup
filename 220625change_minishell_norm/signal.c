/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:36:12 by yukim             #+#    #+#             */
/*   Updated: 2022/06/28 13:55:22 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	ctrl_c();
static void ctrl_bs();
static void ft_sig_handler_in_heredoc(int sig_num);

void	handler_tmp(int sig)
{
	if (sig == SIGINT)
		ft_error_message("\n", 130);
	if (sig == SIGQUIT)
		printf("Quit: %d\n", sig);
}

void	ft_sig_handler(int sig_num)
{
// 	ft_error_message("Called : sig_handler\n", 222);
	if (data.heredoc_flag == TRUE)
		ft_sig_handler_in_heredoc(sig_num);
	else if (sig_num == SIGINT)
	{
		ctrl_c();
	}
	else if (sig_num == SIGQUIT)
	{
		ctrl_bs();
	}
	
}
static void ft_sig_handler_in_heredoc(int sig_num)
{
	// ft_error_message("Called : ft_sig_handler_in_heredoc\n", 222);
	if (sig_num == SIGINT)
	{
		close(STDIN_FILENO);
		ft_error_message("\n", 1);
		rl_on_new_line();
		if (data.p_flag == TRUE)
		{
			data.exit_status = 130;
			exit(data.exit_status);
		}
	}
}

static void	ctrl_c()
{
	//ft_error_message("Called : ctrl_c \n", 222);
	
	ft_error_message("\n", 1);
	rl_on_new_line();
	// printf("data.p_flag = %d\n", data.p_flag);
	if (data.p_flag == TRUE)
	{
		data.exit_status = 130;
		exit(data.exit_status);
	}
	rl_replace_line("", 0);
	rl_redisplay();
	
	// if(data.heredoc_flag == TRUE)
	// 	close(STDIN_FILENO);
	// if (data.p_flag == TRUE)
	// {
	// 	ft_error_message("\n", 130);
	// 	rl_on_new_line();
	// 	exit(data.exit_status);
	// }
	// else if (data.p_flag == FALSE)
	// {
	// 	ft_error_message("\n", 1);
	// 	rl_on_new_line();
		// if(data.heredoc_fd == FALSE);
		// {
		// 	rl_replace_line("", 0);
		// 	rl_redisplay();
		// }
		/*
		int rl_on_new_line (void) 
			: Tell the update functions that we have moved onto a new (empty) line, 
				usually after outputting a newline.
		void rl_replace_line(char *text, int clear_undo) 
			: clear_undo가 0이 아니면, undo list를 클리어해줌
		void rl_redisplay (void)
			: Change what's displayed on the screen to reflect the current contents of rl_line_buffer.
		*/
	// }
}

static void ctrl_bs()
{
	// char	*len;
//	ft_error_message("Called : ctrl_bs \n", 222);
	
	int	buffer_len;

	buffer_len = ft_strlen(rl_line_buffer);
	// printf("buffer len : %d\n", buffer_len);
	if (buffer_len != 0)
	{
		// ft_error_message("test buffer_len", 131);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		if (data.p_flag == TRUE)
		{
			ft_error_message("Quit: 3\n", 131);
			exit(data.exit_status);
		}
	}
	else if (buffer_len == 0)
	{
		//SIG_IGN를 주면 해당 시그널을 무시한다
		// signal(SIGQUIT, SIG_IGN);
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
	
	// if (data.p_flag == TRUE)
	// {
	// 	ft_error_message("Quit: 3\n", 131);
	// 	rl_on_new_line();
	// 	exit(data.exit_status);
	// }
	// else if (data.p_flag == FALSE)
	// {
	// 	rl_replace_line("", 0);
	// 	rl_redisplay();
	// 	//SIG_IGN를 주면 해당 시그널을 무시한다
	// 	// signal(SIGQUIT, SIG_IGN);
	// }
}
