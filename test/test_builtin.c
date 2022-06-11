#include "../include/minishell.h"

void	postorderTravelBinSTree(t_astnode *node);

int main()
{
	char *str;
	int 	i = 0;

	//str = "\"abc 'de f'g\" de";
	// str = "export test1='mi  ni' test2='mmmmi  ni' test3='mi ni'";
	str = "unset test1 test2 test3";
	// str = "export test=minishell";
	//str = "export test1='mi  ni'";
	data = ft_calloc(1, sizeof(t_data));
	// token
	printf("wc 4 == %d\n", ft_wordcount(str));
	tokenize_input(data, str);  //  | cd libft | echo hh

	//printf("wc : %d\n",ft_wordcount("abc 'efg' hi"));
	// tokenize에서 ><때문에 wordcnt 에서 
	// error 반환하고 결론적으로 tokenize에서 null 반환하는데 main에선 
	// null 이라 걍 바로 return (error)때려버림
	// 결론은 바로 error return 하면서 main으로 돌아와서 다시 input 받아낼 것 같긴 한데
	// 에러 메세지를 세분화해서 지정해주자는 이야기
	// 사용자의 input이 잘못되어서 더이상 진행하지 못하고 새로운 input을 받게끔 하는 경우엔
	// 1. 뭐가 잘못되었는지 메세지 띄워주기
	// 2. exit_status 변경해주기
	// 3. return ;  || return (NULL); || return (ERROR) 해줘서 minishell은 살아있되 더이상 진행하지 않고 input을 다시 받게끔
	// 4. 뭔가 잘못되었을 때 중지 시키지 않고 exit_status 만 변경시켜주거나 할 경우 계속 진행되다 꼬일 가능성 많음 예를들면 세그폴트라던가....
	// 5. 다음 입력을 받기 전, data 구조체의 plexer와 관련된 것 free && 초기화
	
	// while(data->plexer->pptokens[i])
	// {
	//  	printf("tokenize pptokens[%d] : %s\n", i, data->plexer->pptokens[i]);
	//  	i++;
	// }

	// // lexer
	lexical_analysis(data);
	// i = 0;
	// while(data->plexer->pptokens[i])
	// {
	// 	printf("pptokens[%d] : %s  ", i, data->plexer->pptokens[i]);
	// 	printf("type[%d] : %d\n", i, data->plexer->ptype[i]);
	// 	i++;
	// }

	// //syntax
	syntax_analysis(data);
	init_ast(data);
	printf("ast tree : \n\n\n");
	postorderTravelBinSTree(data->p_ast->prootnode);
	// ft_pwd(data);
	t_astnode *pelement = data->p_ast->prootnode->prightchild;
	// ft_export(data, pelement);
	// printf("exportttttt \n");
	
	char *key;
	char *value;

	key = "test1";
	value = "123";
	insert_envv(data, key, value,TRUE);
	key = "test2";
	value = "122222223";
	insert_envv(data, key, value,TRUE);
	key = "test3";
	value = "1233333333";
	insert_envv(data, key, value,TRUE);
	
	ft_env(data, TRUE);
	ft_env(data, FALSE);
	// ft_echo(data, pelement);

	ft_unset(data, pelement);
	ft_env(data, FALSE);
	printf("%d\n", data->exit_status);
}
