#include<stdio.h>

extern char **environ;

main()
{
	int i;
	for(i=0; environ[i]; i++)
		printf("%s\n",environ[i]);
}