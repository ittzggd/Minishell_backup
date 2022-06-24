#include "../include/minishell.h"

static int	get_type(char *value)
{
	int	type;

	if (!value || *value == '\0')
		type = T_NULL;
	else if (is_pipe(value))
		type = T_PIPE;
	else if (is_redirection(value))
		type = T_REDIRECTION;
	// else if (is_option(value))
	// 	type = T_OPTION;
	else if (is_quote(*value))
	{
		value++;
		type = get_type(value);
		if (type == T_PIPE || type == T_REDIRECTION || type == T_ENV)
			type = T_WORD;
	}
	else
		type = T_WORD;
	return (type);
}

void	lexical_analysis(t_data *data)
{
	char	**tokens;
	int		*type;
	int		i;
	int		command_flag;

	i = 0;
	command_flag = FALSE;
	tokens = data->plexer->pptokens;
	data->plexer->ptype = (int *)ft_calloc(data->tokens_cnt + 1, sizeof(int));
	type = data->plexer->ptype;
	if (!type)
		return ;
	while (tokens[i])
	{
		type[i] = get_type(tokens[i]);
		if(type[i] == T_WORD)
		{
			if (i == 0)
			{
				type[i] = T_COMMAND;
				command_flag = TRUE;
			}
			else if (i != 0 && type[i - 1] == T_PIPE)
			{
				type[i] = T_COMMAND;
				command_flag = TRUE;
			}
			else if (command_flag == FALSE && type[i - 2] == T_REDIRECTION)
			{
				type[i] = T_COMMAND;
				command_flag = TRUE;
			}
		}
		if (type[i] == T_PIPE)
		{
			data->pipe_cnt++;
			command_flag = FALSE;
		}
		else if (type[i] == T_REDIRECTION)
			data->redirection_cnt++;
		else if (type[i] == T_WORD)
		{
			if(i != 0 && type[i - 1] == T_COMMAND)
			{
				if(is_option(tokens[i]))
					type[i] = T_OPTION;
			}
			if (is_env(tokens[i]))
			{
				// $와 괄호를 제외한 key값을 tokens[i]에 저장하기
				replace_env_to_value(i, data);
				if (!data->plexer->pptokens[i])
				{
					data->exit_status = 1;
					return ;
				}
				// 에러처리를 함수 쪼갤때 해주기
			}
		}
		i++;
	}
}

// int main()
// {
// 	char *str;
// 	int 	i = 0;

// 	str = "echo hi";
// 	data = ft_calloc(1, sizeof(t_data));
// 	// token
// 	tokenize_input(data, "echo hi");
// 	while(data->plexer->pptokens[i])
// 	{
// 		printf("tokenize pptokens[%d] : %s\n", i, data->plexer->pptokens[i]);
// 		i++;
// 	}

// 	// lexer
// 	lexical_analysis(data);
// 	i = 0;
// 	while(data->plexer->pptokens[i])
// 	{
// 		printf("pptokens[%d] : %s  ", i, data->plexer->pptokens[i]);
// 		printf("type[%d] : %d\n", i, data->plexer->ptype[i]);
// 		i++;
// 	}
// }
