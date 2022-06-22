// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   save_exec.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/06/20 12:09:53 by yukim             #+#    #+#             */
// /*   Updated: 2022/06/21 20:04:52 by yukim            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "./include/minishell.h"

// int	execv_cmd(char *cmd, t_astnode *argsnode);
// int	builtin_cmd(char *blt_cmd, t_astnode *argsnode);

// void	exec_ast(void)
// {
// 	int	std_fd[2];
	
	
// 	if (pipe(std_fd) < 0)
// 	{
// 		return ;
// 	}
// 	dup2(STDIN_FILENO, std_fd[0]);
// 	dup2(STDOUT_FILENO, std_fd[1]);

// 	if (data.pipe_cnt > 0)
// 		postorder_travel_ast(data.p_ast->prootnode, std_fd);
// 	else
// 		postorder_travel_command(data.p_ast->prootnode, std_fd);

// 	dup2(std_fd[0], STDIN_FILENO);
// 	dup2(std_fd[1], STDOUT_FILENO);
// }

// void	exec_cmd(t_astnode *argsnode)
// {
// 	t_astnode	*argnode;
// 	char		*cmd;
// 	int			cmd_flag;
// 	int			pid;

// 	argnode = argsnode->prightchild;
// 	cmd = data.plexer->pptokens[argnode->pvalue_index[0]];
// 	cmd_flag = 0;
// 	if (builtin_cmd(cmd, argsnode) == TRUE)
// 		cmd_flag++;
// 	if (cmd_flag == 0)
// 	{
// 		if(execv_cmd(cmd, argsnode) == TRUE)
// 			cmd_flag++;
// 	}
// 	if (cmd_flag == 0)
// 		printf("nanoshell : command not found : %s\n", cmd);
// }

// int	builtin_cmd(char *blt_cmd, t_astnode *argsnode)
// {
// 	if (ft_strncmp(blt_cmd, "cd", -1))
// 		ft_cd(argsnode);
// 	else if (ft_strncmp(blt_cmd, "echo", -1))
// 		ft_echo(argsnode); 
// 	else if (ft_strncmp(blt_cmd, "env", -1))
// 		ft_env(FALSE);	// stdout에 출력하지 않고 dup2로 방향 바꿔서 써주기
// 	else if (ft_strncmp(blt_cmd, "exit", -1))
// 		ft_exit(argsnode);
// 	else if (ft_strncmp(blt_cmd, "export", -1))
// 		ft_export(argsnode);
// 	else if (ft_strncmp(blt_cmd, "pwd", -1))
// 		ft_pwd();
// 	else if (ft_strncmp(blt_cmd, "unset", -1))
// 		ft_unset(argsnode);
// 	else
// 		return (FALSE);
// 	return (TRUE);
// }

// int	execv_cmd(char *cmd, t_astnode *argsnode)
// {
// 	int		pid;

// 	pid = fork();
// 	if (pid < 0)
// 		exit(1);
// 	if(pid == 0)
// 	{
// 		if (ft_strnstr(cmd, "nanoshell", ft_strlen("nanoshell")))
// 			ft_nanoshell(cmd);
// 		else if (ft_strncmp(cmd, "sleep", -1))
// 		{
// 			char *argv[3];
// 			char *env[] = {"/bin/sleep", NULL};
// 			argv[0] = "sleep";
// 			argv[1] = "10";
// 			argv[2] = 0;
// 			execve(env[0], argv, env);
// 		}
// 		else if (ft_strncmp(cmd, "cat", -1))
// 		{
// 			char *argv[2];
// 			char *env[] = {"/bin/cat", NULL};
// 			argv[0] = "cat";
// 			argv[1] = 0;
// 			execve(env[0], argv, env);
// 		}
// 		else if (ft_strncmp(cmd, "ls", -1))
// 		{
// 			char *argv[2];
// 			char *env[] = {"/bin/ls", NULL};
// 			argv[0] = "ls";
// 			argv[1] = NULL;
// 			execve(env[0], argv, env);
// 			//execve(env[0], argv, env);
// 		}
// 		else
// 			return (FALSE);
// 	}
// 	return (TRUE);
// }
