#include<stdio.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

#define SHOWHOST

int main()
{
	struct 	utmp current_recond;
	int 	utmpfd;
	int		reclen=sizeof(current_recond);
	
	if((utmpfd=open(UTMP_FILE, O_RDONLY))==-1){
		perror(UTMP_FILE);
		exit(1);
	}
	while(read(utmpfd, &current_recond, reclen)==reclen)
		show_info(&current_recond);
	close(utmpfd);
	return 0;
}

show_info(struct utmp *utbufp)
{
	printf("% -8.8s", utbufp->ut_name);
	printf(" ");
	printf("% -8.8s", utbufp->ut_line);
	printf(" ");
	printf("%10ld", utbufp->ut_time);
	printf(" ");
#ifdef SHOWHOST
	printf("(%s)", utbufp->ut_host);
#endif
	printf("\n");
}