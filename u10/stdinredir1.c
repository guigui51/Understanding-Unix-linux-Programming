#include<stdio.h>
#include<fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<stdlib.h>
#include <unistd.h>

main()
{
	int fd;
	char line[100];
	
	fgets(line, 100, stdin); printf("%s", line);
	fgets(line, 100, stdin); printf("%s", line);
	fgets(line, 100, stdin); printf("%s", line);
	
	close(0);									//关了0，然后新打开的文件描述符是0
	fd=open("/etc/passwd", O_RDONLY);
	if(fd!=0){
		fprintf(stderr, "Could not open data as fd 0\n");
		exit(1);
	}
	
	fgets(line, 100, stdin); printf("%s", line);
	fgets(line, 100, stdin); printf("%s", line);
	fgets(line, 100, stdin); printf("%s", line);	
	
}