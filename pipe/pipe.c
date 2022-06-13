/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:11:47 by yukim             #+#    #+#             */
/*   Updated: 2022/06/13 15:49:53 by hejang           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "string.h"

void	c(t_astnode *cmdnode, int *fd)
{
	t_astnode	*argsnode;
	t_astnode	*argnode;
	char *blt_cmd;
	char *argv;

	argsnode = cmdnode->prightchild;
	argnode = argsnode->prightchild;
	blt_cmd = data->plexer->pptokens[argnode->pvalue_index[0]];

	if (ft_strncmp(blt_cmd, "cd", -1))
		ft_cd(data, argsnode);
	else if (ft_strncmp(blt_cmd, "echo", -1))
		ft_echo(data, argsnode, fd[1]); // 이러면 echo도 printf를 쓰는게 나을 듯
	else if (ft_strncmp(blt_cmd, "env", -1))
		ft_env(data, FALSE);	// stdout에 출력하지 않고 dup2로 방향 바꿔서 써주기
	else if (ft_strncmp(blt_cmd, "exit", -1))
		ft_exit(data, argsnode);
	else if (ft_strncmp(blt_cmd, "export", -1))
		ft_export(data, argsnode);
	else if (ft_strncmp(blt_cmd, "pwd", -1))
		ft_pwd(data);
	else if (ft_strncmp(blt_cmd, "unset", -1))
		ft_unset(data, argsnode);
	else if (ft_strncmp(blt_cmd, "minishell", -1))
	{
		argv = data->plexer->pptokens[argnode->pvalue_index[0]];
		execve(경로, argv, 환경변수 목록);
	
	}
}

int	fork_pipe(int *fd, int *newfd, t_astnode *pipenode)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return 1;
	if (pid == 0)
	{
		
	}
	else
	{

	}
}

int	ft_pipe_main()
{
	int i;
	pid_t pid;
	int fd[2];
	int newfd[2];
	t_astnode *curr;
	char	*blt_cmd;

	i = 0;
	if (data->pipe_cnt > 0)
	{
		if (pipe(fd) < 0)
			return (1);
		if (pipe(newfd) < 0)
			return (2);
		curr = data->p_ast->prootnode;
		while (i < data->pipe_cnt) // echo "hi" > a.txt | pwd | cd
		{
			pid = fork();
			if (pid < 0)
				return 1;
			if (pid == 0)
			{
				close(fd[0]);
				//fd[1] 에 쓰기

				// 빌트인 명령어일 경우 어떤 함수를 실행해야하는지 찾아야 함,,,, 이게 맞는가ㅏ,,,execve는 어떻게 하는지 알아보기
				exec_cmd(curr->pleftchild, fd);
				// 만약 minishell 이 명령어로 들어온다=> parser의 is_cmd함수 고쳐줬음.
				// 빌트인이 아닌 명령어는 execve로 실행
			}
			else
			{
				curr = curr->prightchild;
				fork_pipe(fd, newfd, curr);
			}
		}
	}
	
}

int	main()
{
	int fd[2];
	int pid;
	
	
	if (pipe(fd) < 0)
		return (1);
	pid = fork();
	if (pid < 0)
		return (2);
	if (pid == 0)
	{
		close(fd[0]);
		int	i;
		scanf(" %d", &i);
		printf("input : %d\n", i);
		write(fd[1], &i, sizeof(int));
		printf("I'm Child Process\n");
		close(fd[1]);
		return (0);
	}
	else
	{
		close(fd[1]);
		int j;
		read(fd[0], &j, sizeof(int));
		close(fd[0]);
		printf("I'm parent Process  j = %d\n", j);
	}


	return (0);
}

