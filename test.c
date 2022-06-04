#include<stdio.h>
#include <stdlib.h>
#include "./include/minishell.h"

int main()
{
	t_data *data = ft_calloc(1, sizeof(t_data));

	char *str = "hello \'sfj\'";
	printf("%p\n", tokenize_input(data, str)); 

}
