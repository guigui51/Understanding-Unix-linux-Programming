#include<stdio.h>
#include<string.h>

int main()
{
	char  *s="hello world";
	printf("1:%s\n", s);
	while(s) *s++;
	strcpy(s, ".");
	printf("2:%s\n", s);
}