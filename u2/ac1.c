#include<stdio.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

/* #define SHOWHOST*/
void showtime(long);
void show_info(struct utmp*);

int main()
{
	struct 	utmp utbuf;
	struct 	utmp copy;
	int 	utmpfd;
	static long 	total=0;
	
	if((utmpfd=open("/var/log/wtmp", O_RDONLY))==-1){
		perror(UTMP_FILE);
		exit(1);
	}
	
	while(read(utmpfd, &utbuf, sizeof(utbuf))==sizeof(utbuf)){
		printf("%s\n",utbuf.ut_id);
		printf("%d\n", utbuf.ut_time);
		if(strcmp(utbuf.ut_id,"~~")==0){
			total=utbuf.ut_time-copy.ut_time+total;	
			
		}
		else
			copy=utbuf;	
	}
	printf("total  %d\n",total);
	close(utmpfd);
	return 0;
}

