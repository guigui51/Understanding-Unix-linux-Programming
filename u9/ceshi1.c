#include<stdio.h>

#define is_delim(x)((x)==1)

int main()
{
	int a=1;
	int b=2;
	printf("%d\n", is_delim(a));
	printf("%d\n", is_delim(b));
	return 1;
}