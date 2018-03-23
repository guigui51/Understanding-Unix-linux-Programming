#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<time.h>
#include<string.h>
#include<arpa/inet.h>
#include"socklib.h"

#define	HOSTLEN 256
#define	BACKLOG	1

int make_server_socket_q(int ,int);

int make_server_socket(int portnum)
{
	return make_server_socket_q(portnum, BACKLOG);
}

int make_server_socket_q(int portnum, int backlog)
{
	struct 	sockaddr_in saddr;
	struct 	hostent 		*hp;
	char	hostname[HOSTLEN];
	int		sock_id;
	
	sock_id=socket(AF_INET, SOCK_STREAM, 0);
	if(sock_id==-1)
		return -1;
	
	/*原书代码
	bzero((void *)&saddr, sizeof(saddr));
	
	gethostname(hostname, HOSTLEN);
	hp=gethostbyname(hostname);
	
	bcopy((void *)hp->h_addr, (void *)&saddr.sin_addr,
			hp->h_length);
	saddr.sin_port=htons(PORTNUM);
	saddr.sin_family=AF_INET;
	*/
	bzero((void *)&saddr, sizeof(saddr));
	saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr=htonl(INADDR_ANY);
	saddr.sin_port=htons(portnum);
	
	if(bind(sock_id, (struct sockaddr *)&saddr, sizeof(saddr))!=0)
		return -1;
	
	if(listen(sock_id, 1)!=0)
		return -1;
	return sock_id;
	
}

int connect_to_server(char *host, int portnum)
{
	int sock;
	struct	sockaddr_in	servadd;
	struct	hostent		*hp;
	
	sock=socket(AF_INET, SOCK_STREAM, 0);
	if(sock==-1)
		return -1;
	
	/*原书代码
		bzero(&servadd, sizeof(servadd));
		hp=gethostbyname(av[1]);
		if(hp==NULL)
			oops(av[1]);
		bcopy(hp->h_addr, (struct sockaddr *)&servadd.sin_addr, hp->h_length);
		servadd.sin_port=htons(PORTNUM);
		servadd.sin_family=AF_INET;
		*/
	bzero(&servadd, sizeof(servadd));
	servadd.sin_family=AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &servadd.sin_addr);
	servadd.sin_port=htons(portnum);
	
	if(connect(sock, (struct sockaddr *)&servadd, sizeof(servadd))!=0)
		return -1;
	return sock;
}
