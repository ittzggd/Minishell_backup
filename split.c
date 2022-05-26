#include <stdio.h>

int	ft_wordcount(char *str);

int main()
{
	int		i;
	char 	*str;

//	scanf("%s\n", str);
	i = ft_wordcount("echo 'hi hi'> 'a.txt'");
	printf("%d\n", i);


}

int	ft_wordcount(char *str)
{
	int	i;
	int	wc;
	int	quote;

	i = 0;
	quote = 0;
	wc = 0;
	while (str[i])
	{
		if (str[i] && str[i] != ' ' && quote == 0) //탭, 개행 문자
		{
			wc++;
			while (str[i] && (str[i] != ' ' || quote > 0))
			{
				if (str[i] == 34 && quote == 0)
					quote = 2;
				else if (str[i] == 39 && quote == 0)
					quote = 1;
				else if (str[i] == 34 && quote == 2)
					quote = 0;
				else if (str[i] == 39 && quote == 1)
					quote = 0;
				i++;
			}
		}// 공백 다
		else
			i++;
	}
	return (wc);
}
