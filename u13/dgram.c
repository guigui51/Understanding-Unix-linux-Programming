#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<time.h>
#include<string.h>
#include<arpa/inet.h>


#define	HOSTLEN 256

int make_internet_address();

int make_dgram_server_socket(int portnum)
{
	struct 	sockaddr_in saddr;
	char	hostname[HOSTLEN];
	int		sock_id;
	
	sock_id=socket(AF_INET, SOCK_DGRAM, 0);
		if(sock_id==-1)
			return -1;
	
	//strcpy(hostname, "127.0.0.1");
	gethostname(hostname, HOSTLEN);
	make_internet_address(hostname, portnum, &saddr);
		/*
	bzero(&saddr, sizeof(saddr));
	saddr.sin_addr.s_addr=htonl(INADDR_ANY);
	saddr.sin_port=htons(portnum);
	saddr.sin_family=AF_INET;
	*/
	if(bind(sock_id, (struct sockaddr *)&saddr, sizeof(saddr))!=0)
		return -1;
	
	return sock_id;
}

int make_dgram_client_socket()
{
	return socket(AF_INET, SOCK_DGRAM, 0);
}

int make_internet_address(char *hostname, int port, struct sockaddr_in *addrp)
{
	struct	hostent	*hp;
	
	bzero((void*)addrp, sizeof(struct sockaddr_in));
	hp=gethostbyname(hostname);
	if(hp==NULL)
		return -1;
	bcopy((void *)hp->h_addr, (void *)&addrp->sin_addr, hp->h_length);
	addrp->sin_port=htons(port);
	addrp->sin_family=AF_INET;
	/*
	bzero((void*)addrp, sizeof(struct sockaddr_in));
	inet_pton(AF_INET, hostname, (struct sockaddr *)&addrp->sin_addr);
	addrp->sin_port=htons(port);
	addrp->sin_family=AF_INET;
	*/
	return 0;
}

int get_internet_address(char *host, int len, int *portp, struct sockaddr_in *addrp)
{
	strncpy(host, inet_ntoa(addrp->sin_addr), len);
	*portp=ntohs(addrp->sin_port);
	return 0;
}
