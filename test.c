#include<stdio.h>
#include <stdlib.h>

int main()
{
	int *num;
	int *tmp;
	int	*i;
	int	j;

	tmp = malloc(sizeof(int) * 3);
	num = tmp;
	j = 4;
	i = &j;
	printf("i : %lu\n", sizeof(i));
	printf("*i : %lu\n", sizeof(*i));
	printf("tmp : %lu\n", sizeof(tmp));
	printf("*tmp : %lu\n", sizeof(*tmp));
	printf("num : %lu\n", sizeof(num));
	printf("*num : %lu\n", sizeof(*num));

}
