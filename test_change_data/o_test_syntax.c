#include "./include/minishell.h"

// void	syntax_analysis(void)
// {
	
// }

static void	syntax_error(int *ret_status);

int	syntax_analysis(void)
{
	int		curr;
	int		prev;
	int		ret_status;
	int		*type;
	char	**tokens;
	
	curr = 0; 
	ret_status = 0;
	type = data.plexer->ptype;
	tokens = data.plexer->pptokens;
	printf("exit->status : %d\n", data.exit_status);
	while(curr < data.tokens_cnt)
	{
		prev = curr - 1;
		if(type[curr] == T_COMMAND)
		{
			if (curr != 0 && (type[prev] == T_REDIRECTION || type[prev] == T_OPTION || type[prev] == T_COMMAND))
				type[curr] = T_WORD;
		}
		else if(type[curr] == T_OPTION)
		{
			if (curr != 0 && ((type[prev] == T_COMMAND && !ft_strncmp(tokens[prev], "echo", -1))
				|| type[prev] != T_COMMAND))
				syntax_error(&ret_status);
			// {
			// 	printf("option_ERROR\n");
			// 	exit(0);
			// }
		}
		else if(type[curr] == T_REDIRECTION)
		{
			//if (curr != 0 && (type[prev] == T_PIPE || type[prev] == T_REDIRECTION))
			if (type[curr + 1] != T_WORD  || (curr != 0 && (type[prev] == T_REDIRECTION)))
				syntax_error(&ret_status);
			// {
			// 	printf("red_ERROR\n");
			// 	exit(0);
			// 	// ERROR;
			// }
		}
		else if (curr == 0) //첫자리가 !CMD && !Redirection == ERROR
			syntax_error(&ret_status);
		// {
		// 	printf("1st_ERROR\n");// => command not found	
		// 	exit(0);
		// }
		else if (type[curr] == T_PIPE)
		{
			if((type[curr + 1] != T_COMMAND && type[curr + 1] != T_REDIRECTION) || (curr != 0 && type[prev] == T_REDIRECTION))
				syntax_error(&ret_status);
			// {
			// 	printf("pipe_ERROR\n");
			// 	exit(0);
			// 	// ERROR
			// }
		}
		// else if (type[curr] == T_WORD)
		// {
			
		// }
		else if (type[curr] == T_NULL)
		{
			if (curr != 0 && (type[prev] == T_REDIRECTION || type[prev] == T_PIPE))
			{
				printf("null_ERROR\n");
				exit(0);
			}
		}
		
		curr++;
	}
	return (ret_status);
}

static void	syntax_error(int *ret_status)
{
	printf("nanoshell: syntax error near unexpected token\n");
	*ret_status = 258;
}

