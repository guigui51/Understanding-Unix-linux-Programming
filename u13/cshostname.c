#include <netdb.h>
#include <sys/socket.h>
#include<stdio.h>
#include <unistd.h>
#include <stdio.h>     
#include <sys/socket.h>     
#include <netinet/in.h>     
#include <arpa/inet.h>     
#include <string.h>   

int main(int argc, char **argv)
{
 struct hostent *hptr;
 char **pptr;
 char hostname[32];
 char str[32];
 
 if( gethostname(hostname,sizeof(hostname)) )
 {
  printf("gethostname calling error/n");
  return 1;
 }
 printf("localhost name:%s/n",hostname);
 if( (hptr = gethostbyname(hostname)) == NULL)
 {
  printf("gethostbyname calling error/n");
  return 1;
 }
 pptr=hptr->h_addr_list;
 for(;*pptr!=NULL;pptr++)
  printf("  address:%s/n", inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
 
 return 0;
}

