#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<time.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>

#define oops(m, x) {perror(m);exit(x);}

int make_dgram_server_socket(int);
int get_internet_address(char *, int, int*, struct sockaddr_in*);
void say_who_called(struct sockaddr_in*);
void reply_to_sender(int, char *, struct sockaddr_in*, socklen_t);

int main(int ac, char *av[])
{
	int		port;
	int		sock;
	char	buf[BUFSIZ];
	size_t	msglen;
	struct	sockaddr_in	saddr;
	socklen_t	saddrlen;
	
	if(ac==-1|| (port=atoi(av[1]))<=0){
		fprintf(stderr, "usage: dgrecv portnumber\n");
		exit(1);
	}
	
	if((sock=make_dgram_server_socket(port))==-1)
		oops("cannot make socket", 2);
	
	saddrlen=sizeof(saddr);
	while((msglen=recvfrom(sock, buf, BUFSIZ, 0, (struct sockaddr *)&saddr, &saddrlen))>0)
	{
		buf[msglen]='\0';
		printf("dgrecv: got a message: %s\n", buf);
		say_who_called(&saddr);
		reply_to_sender(sock, buf, &saddr, saddrlen);
	}
	return 0;
}

void reply_to_sender(int sock, char *msg, struct sockaddr_in *addrp, socklen_t len)
{
	char reply[BUFSIZ+BUFSIZ]="Thanks for your %d char message\n";
	
	//sprintf(reply,"Thanks for your %d char message\n", strlen(msg));
	sendto(sock, reply, strlen(reply), 0,  (struct sockaddr *)&addrp, len);
}

void say_who_called(struct sockaddr_in *addrp)
{
	char	host[BUFSIZ];
	int		port;
	
	get_internet_address(host, BUFSIZ, &port, addrp);
	printf(" from: %s: %d\n", host, port);
}

