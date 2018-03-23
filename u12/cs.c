#include<stdio.h>
#include<string.h>

int main()
{
	char *aa="hello to 111 533 666 999 44";
	char	cmd[BUFSIZ], arg[BUFSIZ];
	if(sscanf(aa, "%s%s", cmd, arg+2)!=2)
		printf("!=2\n");
	printf("cmd:%s\n", cmd);
	printf("arg:%s\n", arg);
	return 1;
}