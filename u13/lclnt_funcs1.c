#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

static	int		pid=-1;
static	int		sd=-1;
static	struct	sockaddr	serv_addr;
static	socklen_t	serv_alen;
static	char	ticket_buf[128];
static	have_ticket=0;

#define	MSGLEN	128
#define	SERVER_PORTNUM	2020
#define	HOSTLEN	512
#define	oops(p)	{perror(p); exit(1);}

char *do_transaction();

setup()
{
	char	hostname[BUFSIZ];
	
	pid=getpid();
	sd=make_dgram_client_socket();
	if(sd==-1)
		oops("cannot create socket");
	gethostname(hostname, HOSTLEN);
	make_internet_address(hostname, SERVER_PORTNUM, &serv_addr);
	serv_alen=sizeof(serv_addr);
}

shut_down()
{
	close(sd);
}

int get_ticket()
{
	char	*response;
	char	buf[MSGLEN];
	
	if(have_ticket)
		return(0);
	
	sprintf(buf, "HELO %d", pid);
	
	if((response=do_transaction(buf))==NULL)
		return(-1);
	
	if(strncmp(response, "TICK", 4)==0){
		strcpy(ticket_buf, response+5);
		have_ticket=1;
		narrate("got ticket", ticket_buf);
		return(0);
	}
	if(strncmp(response, "FALL", 4)==0)
		narrate("Could not get ticket", response);
	else
		narrate("Unknown message:", response);
	return(-1);
}

int release_ticket()
{
	char	buf[MSGLEN];
	char	*response;
	
	if(!have_ticket)
		return(0);
	
	sprintf(buf, "GBYE %s", ticket_buf);
	if((response=do_transaction(buf))==NULL)
		return(-1);
	
	if(strncmp(response, "THNX", 4)==0){
		narrate("released ticket OK","");
		return 0;
	}
	
	if(strncmp(response, "FALL", 4)==0)
		narrate("release failed", response+5);
	else
		narrate("Unknown message:", response);
	return(-1);
}

char *do_transaction(char *msg)
{
	static	char	buf[MSGLEN];
	struct	sockaddr	retaddr;
	socklen_t	addrlen=sizeof(retaddr);
	int 	ret;
	
	ret=sendto(sd, msg, strlen(msg), 0, &serv_addr, serv_alen);
	if(ret==-1){
		syserr("sendto");
		return(NULL);
	}
	
	ret=recvfrom(sd, buf, MSGLEN, 0, &retaddr, &addrlen);
	if(ret==-1){
		syserr("recvfrom");
		return(NULL);
	}
	
	return(buf);
}

narrate(char *msg1, char *msg2)
{
	fprintf(stderr, "CLIENT [%d]: %s %s\n", pid, msg1, msg2);
}

syserr(char *msg1)
{
	char	buf[MSGLEN];
	sprintf(buf, "CLIENT [%d]: %s", pid, msg1);
	perror(buf);
}
