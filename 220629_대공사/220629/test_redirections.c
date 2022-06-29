/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:55:52 by yukim             #+#    #+#             */
/*   Updated: 2022/06/30 00:54:13 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	out_red(char *filename)
{
	int	fd;
	
	fd = open(filename, O_WRONLY|O_TRUNC, 0666); // 이미 존재하는 파일이면 내용 삭제 후 적기
	if (fd < 0) // 파일이 존재 하지 않으면, 새로 생성
	{
		fd = open(filename, O_WRONLY|O_CREAT|O_EXCL, 0666);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	in_red(char *filename)
{
	int	fd;
	
	ft_error_message("in_red\n", 222);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_error_message("minishell: ", 1);
		ft_error_message(filename, 1);
		ft_error_message(" No such file or directory\n", 1);
		return ;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	append_red(char *filename)
{
	// >>

	int	fd;

	fd = open(filename, O_WRONLY|O_APPEND, 0666); // 이미 존재하는 파일이면 내용 삭제 후 적기
	if (fd < 0) // 파일이 존재 하지 않으면, 새로 생성
	{
		fd = open(filename, O_WRONLY|O_CREAT|O_EXCL, 0666);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	heredoc(char *delimiter)
{
	int	i;
	int	read_fd;

	i = 0;
	while (i < data.heredoc_cnt)
	{
		if (ft_strncmp(data.heredoc_delimiter[i], delimiter, -1))
			break;
		i++;
	}
	read_fd = data.heredoc_fd[i].fd[0];
	dup2(read_fd, STDIN_FILENO);
	close(read_fd);
}