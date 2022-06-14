#include "../include/minishell.h"

void	exec_cmd(t_astnode *cmdnode)
{
	t_astnode	*argsnode;
	t_astnode	*argnode;
	char *blt_cmd;

	argsnode = cmdnode->prightchild;
	argnode = argsnode->prightchild;
	blt_cmd = data->plexer->pptokens[argnode->pvalue_index[0]];

	if (ft_strncmp(blt_cmd, "cd", -1))
		ft_cd(data, argsnode);
	else if (ft_strncmp(blt_cmd, "echo", -1))
		ft_echo(data, argsnode); 
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
}
