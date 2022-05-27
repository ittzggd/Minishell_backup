#include<stdio.h>

# define TRUE 1
# define FALSE 0
# define ERROR -1

enum quote_flag
{
	SINGLE_QUOTE = 1,
	DOUBLE_QUOTE
};

static int	is_ifs(const char c)
{
	return ((c == '\n' || c == '\t' || c == ' '));
}

int is_pipe(const char *s)
{
	int	p_cnt;

	p_cnt = 0;
	while(*s == '|')
	{
		p_cnt++;
		if (p_cnt > 1)
			return (ERROR);
		s++;
	}
	return (p_cnt);
}

static int	is_redirection(const char *s)
{
	int	r_cnt;

	r_cnt = 0;
	while(*s == '<' || *s == '>')
	{
		r_cnt++;
		// 밑의 경우일 경우 에러 문구 출력 후 다음 입력 받기 (readline) 
		if (r_cnt > 2 || (r_cnt == 2 && *s != *(s - 1)))  // <>    ><   >>>>> 경우 예외처리
			return (ERROR); //// redirection ERROR : zsh: parse error near `>'
		s++;
	}
	return (r_cnt);
}

static int	is_quote(const char c)
{
	if (c == '\'')
		return (SINGLE_QUOTE);
	else if(c == '\"')
		return (DOUBLE_QUOTE);
	return (FALSE);
}

int	ft_wordcount(char const *str)
{
	int	i;
	int	wc;
	int	quote;

	i = 0;
	quote = 0;
	wc = 0;
	while (str[i])
	{
		if (str[i] && is_quote(str[i]))
		{
			quote = is_quote(str[i]);
			while(str[i] && quote != 0)
			{
				i++;
				if(quote == is_quote(str[i]))
					quote = 0;
			}
			i++;
			//wc++;
		}
		else if (str[i] && is_redirection(&str[i]))
		{
			if (is_redirection(&str[i]) == ERROR)
				return (ERROR);
			while (str[i] && is_redirection(&str[i]))
				i++;
			//wc++;
		}
		else if (str[i] && is_ifs(str[i]))
		{
			while (str[i] && is_ifs(str[i]))
				i++;
			continue ;
		}
		else if (str[i] && is_pipe(&str[i]))
		{
			//wc++;
			i++;
		}
		else 
		{
			while (str[i] && !is_ifs(str[i]) && !is_redirection(&str[i]) && !is_quote(str[i]) && !is_pipe(&str[i]))
				i++;
			//wc++;
		}
		wc++;
	}
	return (wc);
}

int main()
{
	int		i;
	char 	*str;

	i = ft_wordcount("echo|'hi hi' ''>a.txt|ls -al");
	printf("9 == %d\n", i);
	i = ft_wordcount("|");
	printf("1 == %d\n", i);
//	scanf("%s\n", str);
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
