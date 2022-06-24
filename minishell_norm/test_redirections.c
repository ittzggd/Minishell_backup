/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:55:52 by yukim             #+#    #+#             */
/*   Updated: 2022/06/24 16:00:56 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"
#include <termios.h>

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
		write(2, "minishell: " ,11);
		write(2, filename, ft_strlen(filename));
		write(2, " No such file or directory\n", 27);
		data.exit_status = 1;
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
	close(data.heredoc_fd[1]);
}

// void in_red()
// {
// 	//     <   : 뒤에온 파일명이 존재하는지만 알면 된다!

// 	int	fd; 
// 	char	*str = "echo < amazing.txt";
// 	t_astnode *filepath_node;

// 	data = ft_calloc(1, sizeof(t_data));
// 	tokenize_input(data, str);
// 	lexical_analysis(data);
// 	syntax_analysis(data);

// 	init_ast(data);
	

// 	filepath_node = data.p_ast->prootnode->pleftchild->pleftchild->prightchild;
// 	char	*filepath = data.plexer->pptokens[filepath_node->pvalue_index[0]];
// 	fd = open(filepath, O_WRONLY|O_APPEND, 0666);
// 	if(fd < 0)
// 	{
// 		printf("minishell: %s: No such file or directory\n", filepath);
// 		return (ERROR);
// 		data.exit_status = 1;
// 	}
// 	dup2(fd, 1);
	
// 	exec_cmd(data.p_ast->prootnode);
// }

// void out_red()
// {
//     // > 
// 	int	fd;
// 	char	*str = "echo 'hihihihi' > a.txt";
// 	t_astnode *filepath_node;

// 	data = ft_calloc(1, sizeof(t_data));
// 	tokenize_input(data, str);
// 	lexical_analysis(data);
// 	syntax_analysis(data);

// 	init_ast(data);
	

// 	filepath_node = data.p_ast->prootnode->pleftchild->pleftchild->prightchild;
// 	char	*filepath = data.plexer->pptokens[filepath_node->pvalue_index[0]];
// 	fd = open(filepath, O_WRONLY|O_TRUNC, 0666); // 이미 존재하는 파일이면 내용 삭제 후 적기
// 	if (fd < 0) // 파일이 존재 하지 않으면, 새로 생성
// 	{
// 		fd = open(filepath, O_WRONLY|O_CREAT|O_EXCL, 0666);
// 	}
// 	dup2(fd, 1);
	
// 	exec_cmd(data.p_ast->prootnode);
// }

// void append_red()
// {
// 	// >>

// 	int	fd;
// 	char	*str = "echo 'iiiiiiiiiii' >> b.txt";
// 	t_astnode *filepath_node;

// 	data = ft_calloc(1, sizeof(t_data));
// 	tokenize_input(data, str);
// 	lexical_analysis(data);
// 	syntax_analysis(data);

// 	init_ast(data);
	

// 	filepath_node = data.p_ast->prootnode->pleftchild->pleftchild->prightchild;
// 	char	*filepath = data.plexer->pptokens[filepath_node->pvalue_index[0]];
// 	fd = open(filepath, O_WRONLY|O_APPEND, 0666); // 이미 존재하는 파일이면 내용 삭제 후 적기
// 	if (fd < 0) // 파일이 존재 하지 않으면, 새로 생성
// 	{
// 		fd = open(filepath, O_WRONLY|O_CREAT|O_EXCL, 0666);
// 	}
// 	dup2(fd, 1);
	
// 	exec_cmd(data.p_ast->prootnode);
// }
