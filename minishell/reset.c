/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:27:53 by yukim             #+#    #+#             */
/*   Updated: 2022/06/27 15:50:36 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	reset_signal(void)
{
	signal(SIGINT, ft_sig_handler);
	signal(SIGQUIT, ft_sig_handler);
}

void	reset_stdfd(void)
{
	dup2(data.std_fd[0], STDIN_FILENO);
	dup2(data.std_fd[1], STDOUT_FILENO);
}