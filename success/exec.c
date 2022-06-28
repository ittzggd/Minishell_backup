/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hejang <hejang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:07:14 by yukim             #+#    #+#             */
/*   Updated: 2022/06/24 17:33:435 by hejang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	execve_cmd(t_astnode *argsnode);

void	exec_ast(void)
{
	// if (pipe(data.heredoc_fd) < 0)
	// {
	// 	data.exit_status = 1;
	// 	return ;
	// }
	// close(data.std_fd[0]);
	// close(data.std_fd[1]);
	// data.std_fd[0] = dup(STDIN_FILENO);
	// data.std_fd[1] = dup(STDOUT_FILENO);

	if (data.pipe_cnt > 0)
		postorder_travel_ast(data.ast.prootnode);
	else
		postorder_travel_command(data.ast.prootnode);

	// dup2(data.std_fd[0], STDIN_FILENO);
	// dup2(data.std_fd[1], STDOUT_FILENO);
	// close(data.std_fd[0]);
	// close(data.std_fd[1]);
	// close(data.heredoc_fd[0]);
	// close(data.heredoc_fd[1]); // heredoc함수에서 닫아줬음
}

void	exec_cmd(t_astnode *argsnode)
{
	t_astnode	*argnode;
	char *blt_cmd;

	argnode = argsnode->prightchild;
	blt_cmd = data.lexer.pptokens[argnode->pvalue_index[0]];

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
}

void	execve_cmd(t_astnode *argsnode)
{
	t_astnode	*argnode;
	int			i;
	int			j;
	char 		*execve_cmd;
	char		**argv;
	pid_t		pid;
	pid_t		pid2;
	char		**envp;
	struct stat	*buf;
	char		**filepath;
	int			idx;
	
	data.exit_status = 0;
	argnode = argsnode->prightchild;
	execve_cmd = data.lexer.pptokens[argnode->pvalue_index[0]];
	idx = 0;
	filepath = join_filepath(execve_cmd);
	i = 0;
	j = 0;
	while(argnode->pvalue_index[i] != -1)
		i++;
	argv = (char **)ft_calloc(i + 1, sizeof(char *));
	while(j < i)
	{
		argv[j] = ft_strdup(data.lexer.pptokens[argnode->pvalue_index[j]]);
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
		data.p_flag = TRUE;
		if(pid == 0)	
		{
			pid2 = fork();
			if(pid2 == 0)
			{
				if (ft_strnstr(execve_cmd, "nanoshell", ft_strlen(execve_cmd)))
					ft_nanoshell(execve_cmd);
				else
				{
					while(filepath[idx])
					{
						if (execve(filepath[idx], argv, NULL) == -1)
							idx++;
						else
							break ;
					}
					if(!filepath[idx])
					{
						printf("nanoshell : command not found : %s\n", argv[0]);
						data.exit_status = 1;
						exit(data.exit_status);
					}
				}
			}
			else
			{
				waitpid(pid, &data.exit_status, 0);
				return ;
			}
		}
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			waitpid(pid, &data.exit_status, 0);
		}
	}
	else
	{
		if (ft_strnstr(execve_cmd, "nanoshell", ft_strlen(execve_cmd)))
			ft_nanoshell(execve_cmd);
		else
		{
			while(filepath[idx])
			{
				if (execve(filepath[idx], argv, NULL) == -1)
					idx++;
				else
					break ;
			}
			if(!filepath[idx])
			{
				printf("nanoshell : command not found : %s\n", argv[0]);
				data.exit_status = 1;
				exit(data.exit_status);
			}
		}
	}
}

