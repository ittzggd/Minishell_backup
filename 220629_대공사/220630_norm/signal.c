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

void ft_sig_handler_in_heredoc(int sig_num)
{
//	ft_error_message("Called : ft_sig_handler_in_heredoc\n", 222);
	if (sig_num == SIGINT)
	{
		close(STDIN_FILENO);
		ft_error_message("\n", 1);
		rl_on_new_line();
		data.exit_status = 1;
	//	if(data.p_flag == TRUE)	
		//	exit(data.exit_status);
	}
	else if (sig_num == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ctrl_c()
{
	// ft_error_message("hi\n", 222);
	// printf("process ? : %d\n\n", getpid());
	if(data.heredoc_flag == TRUE)
	{
		return ;
		// ft_sig_handler_in_heredoc(SIGINT);
	}	
//	ft_error_message("defalut ctrl_c signal \n", 333);
	if (data.p_flag == TRUE)
	{
		ft_error_message("", 130);
		rl_on_new_line();
		exit(data.exit_status);
	}
	else if ( data.p_flag == FALSE)
	{
		ft_error_message("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
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


void ctrl_bs(int sig_num)
{
	if (data.p_flag == TRUE)
	{
		if(data.heredoc_flag == TRUE)
			return ;
		ft_error_message("Quit: 3\n", 131);
		exit(data.exit_status);
	}
	else if (data.p_flag == FALSE)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}
