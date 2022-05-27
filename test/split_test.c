#include <stdio.h>
#include <stdlib.h>
#include "../minishell.h"

static void ft_free_all(char **ret)
{
	int	i;

	i = 0;
	while (ret[i])
	{
		free(ret[i]);
		i++;
	}
	free(ret);
}

int main()
{
	int		i;
	char	**s;


	i = 0;
	printf("echo|'hi hi' ''>a.txt|ls -al \n");
	s = ft_minishell_split("echo|'hi hi' ''>a.txt|ls -al");
	while(s[i])
	{
		printf("%s\n", s[i]);
		i++;
	}
	ft_free_all(s);
	system("leaks a.out");
	/*i = ft_wordcount("c>>a>a.txt");
	printf("5 == %d\n", i);
	i = ft_wordcount("c>>a> a.txt");
	printf("5 == %d\n", i);
	i = ft_wordcount("c>>>a>a.txt");
	printf("-1 == %d\n", i);
	i = ft_wordcount("c<>>a>a.txt");
	printf("-1 == %d\n", i);
	i = ft_wordcount("c >> a> a.txt");
	printf("5 == %d\n", i);
	i = ft_wordcount("c<<>>a>a.txt");
	printf("-1 == %d\n", i);
	i = ft_wordcount("echo ");
	printf("1 == %d\n", i);
	i = ft_wordcount("echo 'hi hi' > a.txt | ls -al");
	printf("7 == %d\n", i);
	i = ft_wordcount("'hi>a.txt'");
	printf("1 == %d\n", i);*/

}
