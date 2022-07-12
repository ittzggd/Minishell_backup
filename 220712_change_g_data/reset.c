/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:10:39 by yukim             #+#    #+#             */
/*   Updated: 2022/07/12 16:35:39 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	reset_stdfd(t_data *data)
{
	dup2(data->std_fd[0], STDIN_FILENO);
	dup2(data->std_fd[1], STDOUT_FILENO);
}

void	reset_signal(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_bs);
}
