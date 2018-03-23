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
#include<signal.h>
#include<sys/errno.h>

#define	SERVER_PORTNUM 	2020
#define	MSGLEN			128
#define	TICKET_AVAIL	0
#define	MAXUSERS		3
#define	oops(x)	{perror(x); exit(-1);}

int		ticket_array[MAXUSERS];
int		sd=-1;
int		num_tickets_out=0;
char	*do_hello();
char	*do_goodbye();

setup()
{
	sd=make_dgram_server_socket(SERVER_PORTNUM);
	if(sd==-1)
		oops("make socket");
	free_all_tickets();
	return sd;
}

free_all_tickets()
{
	int 	i;
	for(i=0; i<MAXUSERS; i++)
		ticket_array[i]=TICKET_AVAIL;
}

shut_down()
{
	close(sd);
}

handle_request(char *req, struct sockaddr_in *client, socklen_t addlen)
{
	char	*response;
	int		ret;
	
	if(strncmp(req, "HELO", 4)==0)
		response=do_hello(req);
	else if(strncmp(req, "GBYE", 4)==0)
		response=do_goodbye(req);
	else
		response="FAIL invalid request";
	
	narrate("SAID:", response, client);
	ret=sendto(sd, response, strlen(response), 0, client, addlen);
	if(ret==-1)
		perror("SERVER sendto failed");
}

char *do_hello(char *msg_p)
{
	int		x;
	static	char	replybuf[MSGLEN];
	
	if(num_tickets_out>=MAXUSERS)
		return("FAIL no tickets available");
	
	for(x=0; x<MAXUSERS && ticket_array[x]!=TICKET_AVAIL; x++);
	
	if(x==MAXUSERS){
		narrate("database corrupt", "", NULL);
		return("FAIL database corrupt");
	}
	
	ticket_array[x]=atoi(msg_p+5);
	sprintf(replybuf, "TICK %d. %d", ticket_array[x], x);
	num_tickets_out++;
	return(replybuf);
}

char *do_goodbye(char *msg_p)
{
	int pid, slot;
	
	if((sscanf((msg_p+5),"%d. %d", &pid, &slot)!=2)||(ticket_array[slot]!=pid)){
		narrate("Bogus ticket", msg_p+5, NULL);
		return("FAIL invalid ticket");
	}
	
	ticket_array[slot]=TICKET_AVAIL;
	num_tickets_out--;
	
	return("THNX See ya!");
}

narrate(char *msg1, char *msg2, struct sockaddr_in *clientp)
{
	fprintf(stderr, "\t\tSERVER: %s %s", msg1, msg2);
	if(clientp)
		fprintf(stderr, "(%s: %d)", inet_ntoa(clientp->sin_addr), ntohs(clientp->sin_port));
	putc('\n', stderr);
}