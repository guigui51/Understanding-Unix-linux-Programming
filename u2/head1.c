#include<stdio.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>


#define BUFFERSIZE 4096

void oops(char *, char *);

int main(int ac, char *av[])
{
	int in_fd,line=0,n_chars;
	char buf[BUFFERSIZE];
	char out[BUFFERSIZE];
	
	FILE *fp=fopen(av[1],"r");
	for(int i=0; i<10; i++){
		fgets(buf, BUFFERSIZE, fp);
		printf(buf);
	}

	return 1;
	

}

void oops(char *s1, char *s2)
{
	fprintf(stderr, "Error: %s ", s1);
	perror(s2);
	exit(1);
}