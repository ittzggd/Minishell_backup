/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:07:14 by yukim             #+#    #+#             */
/*   Updated: 2022/06/23 21:18:33 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	execve_cmd(t_astnode *argsnode);

void	exec_ast(void)
{
	if (pipe(data.std_fd) < 0)
	{
		return ;
	}
	close(data.std_fd[0]);
	close(data.std_fd[1]);
	data.std_fd[0] = dup(STDIN_FILENO);
	data.std_fd[1] = dup(STDOUT_FILENO);

	if (data.pipe_cnt > 0)
		postorder_travel_ast(data.p_ast->prootnode);
	else
		postorder_travel_command(data.p_ast->prootnode);

	dup2(data.std_fd[0], STDIN_FILENO);
	dup2(data.std_fd[1], STDOUT_FILENO);
	close(data.std_fd[0]);
	close(data.std_fd[1]);
}

void	exec_cmd(t_astnode *argsnode)
{
	t_astnode	*argnode;
	char *blt_cmd;

	argnode = argsnode->prightchild;
	blt_cmd = data.plexer->pptokens[argnode->pvalue_index[0]];

	if (ft_strncmp(blt_cmd, "cd", -1))
		ft_cd(argsnode);
	else if (ft_strncmp(blt_cmd, "echo", -1))
		ft_echo(argsnode); 
	else if (ft_strncmp(blt_cmd, "env", -1))
		ft_env(FALSE);	// stdout에 출력하지 않고 dup2로 방향 바꿔서 써주기
	else if (ft_strncmp(blt_cmd, "exit", -1))
		ft_exit(argsnode);
	else if (ft_strncmp(blt_cmd, "export", -1))
		ft_export(argsnode);
	else if (ft_strncmp(blt_cmd, "pwd", -1))
		ft_pwd();
	else if (ft_strncmp(blt_cmd, "unset", -1))
		ft_unset(argsnode);
	else
		execve_cmd(argsnode);
	// else if (ft_strnstr(blt_cmd, "nanoshell", ft_strlen(blt_cmd)))
	// 	ft_nanoshell(blt_cmd);
	// else if (ft_strncmp(blt_cmd, "sleep", -1))
	// {
	// 	char *argv[3];
	// 	char *env[] = {"/bin/sleep", NULL};
	// 	argv[0] = "sleep";
	// 	argv[1] = "10";
	// 	argv[2] = 0;
	// 	execve(env[0], argv, env);
	// }
	// else if (ft_strncmp(blt_cmd, "cat", -1))
	// {
	// 	char *argv[2];
	// 	char *env[] = {"/bin/cat", NULL};
	// 	argv[0] = "cat";
	// 	argv[1] = 0;
	// 	execve(env[0], argv, env);
	// }
	// else if (ft_strncmp(blt_cmd, "ls", -1))
	// {
	// 	char *argv[2];
	// 	char *env[] = {"/bin/ls", NULL};
	// 	argv[0] = "ls";
	// 	argv[1] = NULL;
	// 	execve(env[0], argv, env);
	// 	//execve(env[0], argv, env);
	// }
	// else
	// {
	// 	printf("nanoshell : command not found : %s\n", blt_cmd);
	// }
}

void	execve_cmd(t_astnode *argsnode)
{
	t_astnode	*argnode;
	int			i;
	int			j;
	char 		*execve_cmd;
	char		**argv;
	pid_t		pid;
	char		**envp;
	struct stat	*buf;
	char		*filepath;
	
	data.exit_status = 0;
	argnode = argsnode->prightchild;
	execve_cmd = data.plexer->pptokens[argnode->pvalue_index[0]];
	i = 0;
	j = 0;
	while(argnode->pvalue_index[i] != -1)
		i++;
	argv = (char **)ft_calloc(i + 1, sizeof(char *));
	while(j < i)
	{
		argv[j] = ft_strdup(data.plexer->pptokens[argnode->pvalue_index[j]]);
		j++;
	}
	argv[j] = NULL;
	if (data.pipe_cnt == 0)
	{
		pid = fork();
		if (pid < 0)
		{
			exit(1);
		}
		if(pid == 0)	
		{
			if (ft_strnstr(execve_cmd, "nanoshell", ft_strlen(execve_cmd)))
				ft_nanoshell(execve_cmd);
			else
			{
				filepath = ft_strjoin("/bin/", argv[0]); // PATH를 :기준 spilt으로 잘라서 모두 경로가 있는지 체크 후 없으면 에러
				if(execve(filepath, argv, NULL) == -1)
				{
					printf("nanoshell : command not found : %s\n", argv[0]);
					data.exit_status = 1;
					exit(data.exit_status);
				}
			}
		}
		else
			waitpid(pid, &data.exit_status, 0);
	}
	else
	{
		int	k = 0;
		while (argv[k])
		{
			printf("\t====\targv[%d] %s\n", k, argv[k]);
			k++;
		}
		filepath = ft_strjoin("/bin/", argv[0]); // PATH를 :기준 spilt으로 잘라서 모두 경로가 있는지 체크 후 없으면 에러
		printf("pipecnt > 0 : filepath : %s\n", filepath);
		if (execve(filepath, argv, NULL) == -1)
		{
			printf("nanoshell : command not found : %s\n", argv[0]);
			data.exit_status = 1;
			exit(data.exit_status);
		}
	}
}
