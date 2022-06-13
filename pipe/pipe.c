/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:11:47 by yukim             #+#    #+#             */
/*   Updated: 2022/06/13 19:41:34 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "string.h"

void	exec_cmd(t_astnode *cmdnode)
{
	t_astnode	*argsnode;
	t_astnode	*argnode;
	char *blt_cmd;
	// char *argv;
	// char **envp;

	argsnode = cmdnode->prightchild;
	argnode = argsnode->prightchild;
	blt_cmd = data->plexer->pptokens[argnode->pvalue_index[0]];

	if (ft_strncmp(blt_cmd, "cd", -1))
		ft_cd(data, argsnode);
	else if (ft_strncmp(blt_cmd, "echo", -1))
		ft_echo(data, argsnode); // 이러면 echo도 printf를 쓰는게 나을 듯
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
	// else if (ft_strncmp(blt_cmd, "minishell", -1))
	// {
	// 	argv = data->plexer->pptokens[argnode->pvalue_index[0]];
	// 	envp = envvlist_to_envp();
	// 	execve(경로, argv, envp);
	
	// }
}



// int	fork_pipe(int *fd, int *newfd, t_astnode *pipenode)
// {
// 	int	pid;

// 	pid = fork();
// 	if (pid < 0)
// 		return 1;
// 	if (pid == 0)
// 	{
				
// 	}
// 	else
// 	{

// 	}
// }

// int	ft_pipe_main()
// {
// 	int 		i;
// 	pid_t 		pid;
// 	int 		fd[2];
// 	int 		newfd[2];
// 	t_astnode 	*curr;

// 	if (data->pipe_cnt > 0)
// 	{
// 		if (pipe(fd) < 0)
// 			return (1);
// 		if (pipe(newfd) < 0)
// 			return (2);
// 		i = 0;
// 		curr = data->p_ast->prootnode;
// 		while (i < data->pipe_cnt) // echo "hi" > a.txt | pwd | cd
// 		{
// 			pid = fork();
// 			if (pid < 0)
// 				return 1;
// 			if (pid == 0)
// 			{
// 				close(fd[0]);
// 				//fd[1] 에 쓰기
// 				// dup2(fd[1], 1);
// 				exec_cmd(curr->pleftchild);
// 				// 리다이렉션 , heredoc 이 있으면 실행
// 			}
// 			else
// 			{
// 				curr = curr->prightchild;
// 				fork_pipe(fd, newfd, curr);
// 			}
// 		}
// 	}
	
// }

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

