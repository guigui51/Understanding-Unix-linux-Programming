#include<stdio.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

/* #define SHOWHOST*/
void showtime(long);
void show_info(struct utmp*);

int main()
{
	struct 	utmp utbuf;
	int 	utmpfd;

	
	if((utmpfd=open(UTMP_FILE, O_RDONLY))==-1){
		perror(UTMP_FILE);
		exit(1);
	}
	
	while(read(utmpfd, &utbuf, sizeof(utbuf))==sizeof(utbuf))
		show_info(&utbuf);
	close(utmpfd);
	return 0;
}

void show_info(struct utmp *utbufp)
{
	printf("% -8.8s", utbufp->ut_name);
	printf(" ");
	printf("% -8.8s", utbufp->ut_line);
	printf(" ");
	showtime(utbufp->ut_time);

#ifdef SHOWHOST
	if(utbufp->ut_host[0]!='\0')
		printf("(%s)", utbufp->ut_host);
#endif
	printf("\n");
}

void showtime(long timeval)
{
	struct tm* cp;
	cp=gmtime(&timeval);
	printf("%d-%d-%d %d:%d", cp->tm_year+1900, cp->tm_mon+1, cp->tm_mday, cp->tm_hour, cp->tm_min);
}