/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:55:52 by yukim             #+#    #+#             */
/*   Updated: 2022/06/27 12:21:52 by yukim            ###   ########.fr       */
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
	dup2(fd, 1);
}

void	in_red(char *filename)
{
	int	fd;
	
	fd = open(filename, O_WRONLY|O_APPEND, 0666);
	if (fd < 0)
	{
		ft_error_message("minishell: ", 1);
		ft_error_message(filename, 1);
		ft_error_message(" No such file or directory\n", 1);
		return ;
	}
	dup2(fd, 1);
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
	dup2(fd, 1);
}

void	heredoc(char *delimiter)
{
	char	*input_str;
	char	*delimiter_without_quote;
	
	if (pipe(data.heredoc_fd) < 0)
	{
		data.exit_status = 1;
		return ;
	}
	data.heredoc_flag = TRUE;
	delimiter_without_quote = remove_quote(delimiter);
	while (1)
	{
		//printf("heredoc while : %s\n", delimiter);
		input_str = readline("heredoc > ");
		if (ft_strncmp(input_str, delimiter_without_quote, -1))
			break ;
		write(data.heredoc_fd[1], input_str, ft_strlen(input_str));
		write(data.heredoc_fd[1], "\n", 1);
	}
	if (delimiter != delimiter_without_quote)
		free(delimiter_without_quote);
	dup2(data.heredoc_fd[0], STDIN_FILENO);
	close(data.heredoc_fd[0]);
	close(data.heredoc_fd[1]);
	data.heredoc_flag = FALSE;
}
