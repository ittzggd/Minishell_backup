/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:36:12 by yukim             #+#    #+#             */
/*   Updated: 2022/06/28 18:02:10 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	ctrl_c();
void	ctrl_bs();

void	ft_sig_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		ctrl_c();
	}
	else if (sig_num == SIGQUIT)
	{
		ctrl_bs();
	}
	
}

void	ctrl_c()
{
	if(data.heredoc_flag == TRUE)
		close(STDIN_FILENO);
	if (data.p_flag == TRUE)
	{
		ft_error_message("", 130);
		rl_on_new_line();
		exit(130);
	}
	else if (data.p_flag == FALSE)
	{
		ft_error_message("\n", 1);
		rl_on_new_line();
		if(data.heredoc_fd == FALSE);
		{
			rl_replace_line("", 0);
			rl_redisplay();
		}
		/*
		int rl_on_new_line (void) 
			: Tell the update functions that we have moved onto a new (empty) line, 
				usually after outputting a newline.
		void rl_replace_line(char *text, int clear_undo) 
			: clear_undo가 0이 아니면, undo list를 클리어해줌
		void rl_redisplay (void)
			: Change what's displayed on the screen to reflect the current contents of rl_line_buffer.
		*/
	}
}

void ctrl_bs()
{
	if (data.p_flag == TRUE)
	{
		ft_error_message("Quit: 3\n", 131);
		exit(data.exit_status);
	}
	else if (data.p_flag == FALSE)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		//SIG_IGN를 주면 해당 시그널을 무시한다
		// signal(SIGQUIT, SIG_IGN);
	}
}
