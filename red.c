/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:46:15 by yukim             #+#    #+#             */
/*   Updated: 2022/06/14 18:43:24 by hejang           ###   ########.fr       */
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
	if(fd < 0)
	{
		dup2(1, 2);
		printf("minishell: %s: No such file or directory\n", filename);
		data->exit_status = 1;
		return (data->exit_status);
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
	
	delimiter_without_quote = remove_quote(delimiter);
	while (1)
	{
		input_str = readline("heredoc > ");
		if (ft_strncmp(input_str, delimiter_without_quote, -1))
			break ;
	}
	if (delimiter != delimiter_without_quote)
		free(delimiter_without_quote);
}
