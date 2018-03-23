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

#define BUFFERSIZE 4096

void oops(char *, char *);

int main(int ac, char *av[])
{
	int in_fd,out_fd, n_chars;
	char buf[BUFFERSIZE];
	

	if(ac==2){
	
		if((in_fd=open(av[1], O_RDONLY))==-1)
			oops("cannot open ",av[1]);
	
		while((n_chars=read(in_fd, buf, BUFFERSIZE))>0)
			if(write(STDOUT_FILENO, buf, n_chars)!=n_chars)
				oops("Write error to ", av[1]);
		close(in_fd);

	}else{
	
		for(int i=1;i!=ac;i++)
		{
			if((in_fd=open(av[i], O_RDONLY))==-1)
				oops("cannot open ",av[i]);
			while((n_chars=read(in_fd, buf, BUFFERSIZE))>0)
				if(write(STDOUT_FILENO, buf, n_chars)!=n_chars)
					oops("Write error to ", av[i]);
			close(in_fd);
		}
	}

}

void oops(char *s1, char *s2)
{
	fprintf(stderr, "Error: %s ", s1);
	perror(s2);
	exit(1);
}