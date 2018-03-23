#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<stdlib.h>
#include<unistd.h>

#define	SOCKET "/tmp/logfilesock"
#define	oops(x,m)	{perror(x); exit(m);}

int main(int ac, char *av[])
{
	int		sock;
	struct	sockaddr_un	addr;
	socklen_t	addrlen;
	char	sockname[]=SOCKET;
	char	*msg=av[1];
	
	if(ac!=2){
		fprintf(stderr, "usage: logfilec 'message'\n");
		exit(1);
	}
	sock=socket(AF_UNIX, SOCK_DGRAM, 0);
	if(sock==-1)
		oops("socket", 2);
	
	addr.sun_family=AF_UNIX;
	strcpy(addr.sun_path, sockname);
	addrlen=strlen(sockname)+sizeof(addr.sun_family);
	
	if(sendto(sock, msg, strlen(msg), 0, &addr, addrlen)==-1)
		oops("sendto", 3); 	
}