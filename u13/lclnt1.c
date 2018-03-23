#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int ac, char *av[])
{
	setup();
	if(get_ticket()!=0)
		exit(0);
	
	do_regular_work();
	
	release_ticket();
	shut_down();
	
}

do_regular_work()
{
	printf("Supersleep version 1.0 Running-Licensed Software\n");
	sleep(10);
}