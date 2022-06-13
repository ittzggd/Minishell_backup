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
}

int main()
{
	/*      > 
	int	fd;
	char	*str = "echo 'hihihihi' > a.txt";
	t_astnode *filepath_node;

	data = ft_calloc(1, sizeof(t_data));
	tokenize_input(data, str);
	lexical_analysis(data);
	syntax_analysis(data);

	init_ast(data);
	

	filepath_node = data->p_ast->prootnode->pleftchild->pleftchild->prightchild;
	char	*filepath = data->plexer->pptokens[filepath_node->pvalue_index[0]];
	fd = open(filepath, O_WRONLY|O_TRUNC, 0666); // 이미 존재하는 파일이면 내용 삭제 후 적기
	if (fd < 0) // 파일이 존재 하지 않으면, 새로 생성
	{
		fd = open(filepath, O_WRONLY|O_CREAT|O_EXCL, 0666);
	}
	dup2(fd, 1);
	
	exec_cmd(data->p_ast->prootnode);
	*/

	/*
	int	fd;   // >>
	char	*str = "echo 'iiiiiiiiiii' >> b.txt";
	t_astnode *filepath_node;

	data = ft_calloc(1, sizeof(t_data));
	tokenize_input(data, str);
	lexical_analysis(data);
	syntax_analysis(data);

	init_ast(data);
	

	filepath_node = data->p_ast->prootnode->pleftchild->pleftchild->prightchild;
	char	*filepath = data->plexer->pptokens[filepath_node->pvalue_index[0]];
	fd = open(filepath, O_WRONLY|O_APPEND, 0666); // 이미 존재하는 파일이면 내용 삭제 후 적기
	if (fd < 0) // 파일이 존재 하지 않으면, 새로 생성
	{
		fd = open(filepath, O_WRONLY|O_CREAT|O_EXCL, 0666);
	}
	dup2(fd, 1);
	
	exec_cmd(data->p_ast->prootnode);
	*/

	//     <   : 뒤에온 파일명이 존재하는지만 알면 된다!

	int	fd;   // >>
	char	*str = "echo < amazing.txt";
	t_astnode *filepath_node;

	data = ft_calloc(1, sizeof(t_data));
	tokenize_input(data, str);
	lexical_analysis(data);
	syntax_analysis(data);

	init_ast(data);
	

	filepath_node = data->p_ast->prootnode->pleftchild->pleftchild->prightchild;
	char	*filepath = data->plexer->pptokens[filepath_node->pvalue_index[0]];
	fd = open(filepath, O_WRONLY|O_APPEND, 0666);
	if(fd < 0)
	{
		printf("minishell: %s: No such file or directory\n", filepath);
		return (ERROR);
		data->exit_status = 1;
	}
	dup2(fd, 1);
	
	exec_cmd(data->p_ast->prootnode);
}
