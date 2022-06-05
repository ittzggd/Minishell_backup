#include  <stdlib.h>
#include  <stdio.h>
 
/* Where the environment variable 'PATH' is set to a value. */
 
int main(void)
{
   char *pathvar;
 
//   printf("%s\n", getenv("PATH"));
	pathvar = getenv("student");
	printf("pathvar=%s",pathvar);
	
}
