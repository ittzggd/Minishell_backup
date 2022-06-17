#include "./include/minishell.h"

char	*tokenize_input(char *input)
{
	int		split_index;

	// if (!input || !data)
	if (!input)
		return (NULL);
	data.tokens_cnt = ft_wordcount(input); // 1. 단어 개수 세기
	if (data.tokens_cnt == ERROR)
		return (NULL);
	data.plexer = ft_calloc(1, sizeof(t_lexer));
	data.plexer->pptokens = (char **)malloc(sizeof(char *) * (data.tokens_cnt + 1));
	if (!data.plexer->pptokens)
		return (NULL); // 2. data.tokens malloc => NULL 체크
	split_index = ft_split_str((char *)input, data.plexer->pptokens);
	if (split_index != data.tokens_cnt)
	{
	 	ft_free_all(data.plexer->pptokens);
		data.plexer->pptokens = NULL;
	}

	int k = 0;
	while (data.plexer->pptokens[k])
	{
		printf("in tokenize__tokens[%d] : %s\n", k, data.plexer->pptokens[k]);
		k++;
	}
	return ("SUCCESS");
}

// int main()
// {
// 	char *str;
// 	int 	i = 0;

// 	str = "echo hi";
// 	data = ft_calloc(1, sizeof(t_data));
// 	tokenize_input(data, "echo hi");
// 	while(data.plexer->pptokens[i])
// 	{
// 		printf("pptokens[%d] : %s\n", i, data.plexer->pptokens[i]);
// 		i++;
// 	}
// }
