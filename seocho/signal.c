/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:36:12 by yukim             #+#    #+#             */
/*   Updated: 2022/06/27 19:57:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	ctrl_c();
static void ctrl_bs();

void	ft_heredoc_sig_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		ft_error_message("heredoc signal\n", 222);
	}
}

void	ft_sig_handler(int sig_num)
{
	// printf("rl_buffer : %s, len = %d\n", rl_line_buffer, ft_strlen(rl_line_buffer));
	if (sig_num == SIGINT)
	{
		// ft_error_message("sig_num == SiGINT\n",222);
		ctrl_c();
	}
	else if (sig_num == SIGQUIT)
	{
		ctrl_bs();
	}
	
}

static void	ctrl_c()
{

	if(data.heredoc_flag == TRUE)
			close(STDIN_FILENO);
	if (data.p_flag == TRUE)
	{
	//	printf("1234");
		ft_error_message("sig_num == SiGINT, p_flag == TRUE\n",222);
		ft_error_message("\n", 130);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit(data.exit_status);
	//	write(data.std_fd[1], "test", 4);
		// write(2, "\n", 1);
		// data.exit_status = 130;
	}
	else if (data.p_flag == FALSE)
	{
		ft_error_message("\n", 1);
		rl_on_new_line();
		
		ft_error_message("sig_num == SiGINT, p_flag == FALSE\n",222);
//		write(data.std_fd[1], "\n", 1);
//		data.exit_status = 1;
		if (data.heredoc_flag == FALSE)
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

static void ctrl_bs()
{
	char	*len;
	int	buffer_len;

	buffer_len = ft_strlen(rl_line_buffer);
	// printf("buffer len : %d\n", buffer_len);
	if (buffer_len != 0)
	{
		// ft_error_message("test buffer_len", 131);
		ft_error_message("Quit: 3\n", 131);
		// write(2, "^\\Quit: 3", ft_strlen("^\\Quit: 3"));
		// data.exit_status = 131;
		if (data.p_flag == TRUE)
			exit(data.exit_status);
	}
	else if (buffer_len == 0)
	{
		//SIG_IGN를 주면 해당 시그널을 무시한다
		// signal(SIGQUIT, SIG_IGN);
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
}
