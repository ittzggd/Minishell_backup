#include<stdio.h>

# define TRUE 1
# define FALSE 0
# define ERROR -1

enum quote_flag
{
	SINGLE_QUOTE = 1,
	DOUBLE_QUOTE
};

static int	is_ifs(char c)
{
	return ((c == '\n' || c == '\t' || c == ' '));
}

static int	is_redirection(char *s, int quote)
{
	int	r_cnt;

	r_cnt = 0;
	if(quote != 0)
		return (FALSE); // 정상
	while(*s == '<' || *s == '>')
	{
		r_cnt++;
		// 밑의 경우일 경우 에러 문구 출력 후 다음 입력 받기 (readline) 
		if (r_cnt > 2 || (r_cnt == 2 && *s != *(s - 1)))  // <>    ><   >>>>> 경우 예외처리
			return (ERROR); //// redirection ERROR : zsh: parse error near `>'
		s++;
	}
/*	if(r_cnt == 1 || r_cnt == 2)
		return (TRUE);
	if(*s != '<' || *s != '>')
		return (FALSE);
	return (TRUE);*/
	return (r_cnt);
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
		if (str[i] && is_ifs(str[i]) == FALSE && quote == 0) //탭, 개행 문자 => isIFS
		{
			wc++;
			while (str[i] && (is_ifs(str[i]) == FALSE || quote > 0))
			{
				if (str[i] == '\"' && quote == 0)
					quote = DOUBLE_QUOTE;
				else if (str[i] == '\'' && quote == 0)
					quote = SINGLE_QUOTE;
				else if (str[i] == '\"' && quote == DOUBLE_QUOTE)
					quote = 0;
				else if (str[i] == '\'' && quote == SINGLE_QUOTE)
					quote = 0;
				else if (is_redirection(&str[i], quote) > 0)
				{ // >>   ,   <<   ,   >   ,  <
					wc++;
					while(str[i] && is_redirection(&str[i], quote))
						i++;
					if(is_ifs(str[i]))
						continue ;
					if(str[i])
						wc++;
				}
				else if (is_redirection(&str[i], quote) == ERROR)
					return (ERROR);
				i++;
			}			
		}
		else
			i++; // 공백 다음 문자위치로 이동
	}
	return (wc);
}

int main()
{
	int		i;
	char 	*str;

//	scanf("%s\n", str);
	i = ft_wordcount("c>>a> a.txt");
	printf("%d\n", i);


}
