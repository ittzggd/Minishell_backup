/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukim <yukim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:07:14 by yukim             #+#    #+#             */
/*   Updated: 2022/06/30 04:46:34 by yukim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	execve_cmd(t_astnode *argsnode);

void	exec_ast(void)
{
	if (data.pipe_cnt > 0)
		postorder_travel_ast(data.ast.prootnode);
	else
		postorder_travel_command(data.ast.prootnode);
}

void	exec_cmd(t_astnode *argsnode)
{
	t_astnode	*argnode;
	char		*blt_cmd;

	argnode = argsnode->prightchild;
	blt_cmd = data.lexer.pptokens[argnode->pvalue_index[0]];
	if (ft_strncmp(blt_cmd, "cd", -1))
		ft_cd(argsnode);
	else if (ft_strncmp(blt_cmd, "echo", -1))
		ft_echo(argsnode);
	else if (ft_strncmp(blt_cmd, "env", -1))
		ft_env(FALSE);
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
	int			cnt;
	char		*execve_cmd;
	char		**argv;
	char		**envp;
	char		**filepath;

	data.exit_status = 0;
	cnt = 0;
	execve_cmd = data.lexer.pptokens[argnode->pvalue_index[0]];
	filepath = join_filepath(execve_cmd);
	while (argsnode->prightchild->pvalue_index[cnt] != -1)
		cnt++;
	argv = create_argv(i, argsnode);
	if (data.pipe_cnt == 0)
		command_without_pipe(execve_cmd, 0, argv);
	else
	{
		if (ft_strnstr(execve_cmd, "nanoshell", ft_strlen(execve_cmd)))
			ft_nanoshell(execve_cmd);
		else
			fork_before_run_execve(filepath, 0, argv);
	}
}

void	command_without_pipe(char *execve_cmd, int idx, char **argv)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		exit(1);
	}
	data.p_flag = TRUE;
	if (pid == 0)
	{
		if (ft_strnstr(execve_cmd, "nanoshell", ft_strlen(execve_cmd)))
			ft_nanoshell(execve_cmd);
		else
			fork_before_run_execve(filepath, idx, argv);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &data.exit_status, 0);
	}
	if (WIFEXITED(data.exit_status))
		data.exit_status = WEXITSTATUS(data.exit_status);
	else if (WIFSIGNALED(data.exit_status))
		data.exit_status = WTERMSIG(data.exit_status) + 128;
}

void	fork_before_run_execve(char *filepath, int idx, char **argv)
{
	pid_t	pid2;

	pid2 = fork();
	if (pid2 == 0)
	{
		reset_signal();
		while (filepath[idx])
		{
			if (execve(filepath[idx], argv, NULL) == -1)
				idx++;
			else
				break ;
		}
		if (!filepath[idx])
			command_not_found_error(argv[0]);
	}
	else
	{
		waitpid(pid2, &(data.exit_status), 0);
		exit(data.exit_status);
	}
}