#include<stdio.h>
#include<unistd.h>

main()
{
	printf("my pid is %d\n", getpid());
	fork();
	fork();
	fork();
	printf("my pid is %d\n", getpid());
}