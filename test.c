#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	int	fd;

	fd = open("./testfile", O_WRONLY);
	for(int i = 0; i < 5; i ++)
	{
		write(fd, "test\n", 5);
	}
}
