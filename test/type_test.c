#include<stdio.h>
#include<stdlib.h>
#include"../minishell.h"

static int	get_type(char *value)
{
	int	type;

	/*
	5. not QUOTE str == word
	6. QUOTE str
		6-1. in quote str
		6-2. in quote cmd
		6-3. in quote option_flag
	7. flag 처리 고민
	*/
	if (!value || *value == '\0')
		type = T_NULL;
	else if (is_pipe(value))
		type = T_PIPE;
	else if (is_redirection(value))
		type = T_REDIRECTION;
	else if (is_cmd(value))
		type = T_COMMAND;
	else if (is_option(value))
		type = T_OPTION;
	else if (is_quote(*value))
	{
		value++;
		type = get_type(value);
		if(type == T_PIPE || type == T_REDIRECTION)
			type = T_WORD;
	}
	else
		type = T_WORD;
	return (type);
}

int main(void)
{
	int	i;

	i = get_type("echo");
	printf("command : %d\n", i);
	i = get_type("hi");
	printf("word : %d\n", i);
	i = get_type("-n");
	printf("option : %d\n", i);
	i = get_type("<<");
	printf("redierection : %d\n", i);
	i = get_type("'echo '");
	printf("word: %d\n", i);
	i = get_type("|");
	printf("pipe: %d\n", i);
	i = get_type("");
	printf("NULL: %d\n", i);
	i = get_type("'|'");
	printf("word: %d\n", i);
	i = get_type("'>'");
	printf("word: %d\n", i);

}