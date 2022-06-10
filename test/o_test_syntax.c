#include "../include/minishell.h"

void	syntax_analysis(t_data *data)
{
	int		curr;
	int		prev;
	int		*type;
	char	**tokens;
	
	curr = 0; 
	type = data->plexer->ptype;
	tokens = data->plexer->pptokens;
	while(curr < data->tokens_cnt)
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
			{
				printf("option_ERROR\n");
				exit(0);
			}
		}
		else if(type[curr] == T_REDIRECTION)
		{
			if (curr != 0 && (type[prev] == T_PIPE || type[prev] == T_REDIRECTION))
			{
				printf("red_ERROR\n");
				exit(0);
				// ERROR;
			}
		}
		else if (curr == 0) //첫자리가 !CMD && !Redirection == ERROR
		{
			printf("1st_ERROR\n");// => command not found	
			exit(0);
		}
		else if (type[curr] == T_PIPE)
		{
			if(type[curr + 1] != T_COMMAND || (curr != 0 && type[prev] == T_REDIRECTION))
			{
				printf("pipe_ERROR\n");
				exit(0);
				// ERROR
			}
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
}


