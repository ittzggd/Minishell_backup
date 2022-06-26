/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:36:12 by yukim             #+#    #+#             */
/*   Updated: 2022/06/26 17:43:59 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

static void	ctrl_c();
static void ctrl_bs();

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

static void	ctrl_c()
{
	if (data.p_flag == TRUE)
	{
		printf("1234");
		write(1, "test", 4);
		write(data.std_fd[1], "\n", 1);
		data.exit_status = 130;
		exit(data.exit_status);
	}
	else if (data.p_flag == FALSE)
	{
		write(data.std_fd[1], "\n", 1);
		data.exit_status = 1;

		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();

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
	if (data.p_flag == TRUE)
	{
		write(2, "^\\Quit: 3", ft_strlen("^\\Quit: 3"));
		data.exit_status = 131;
		exit(data.exit_status);
	}
	else if (data.p_flag == FALSE)
	{
		//SIG_IGN를 주면 해당 시그널을 무시한다
		signal(SIGQUIT, SIG_IGN);
	}
}
