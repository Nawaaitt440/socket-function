#include <stdio.h> //printf
#include <string.h> //memset
#include <stdlib.h> //for exit(0);
#include <sys/socket.h>
#include <errno.h> //for the error no.
#include <netdb.h> //hostent
#include <arpa/inet.h>

int hostname_to_ip(char *,char *);
int main(int argc, char *argv[])
{
	if(argc <2)
	{
		printf("Please provide a hostname to resolve ");
		exit(1);
	}
	char *hostname = argv[1];
	char ip[100];
	hostname_to_ip(hostname, ip);
	printf("%s resolved to %s", hostname, ip);
	printf("\n");
}
/* get ip from dns */

int hostname_to_ip(char *hostname, char *ip)
{
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_in *h;
	int rv;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; //use AF_INET6 to force IPv6
	hints.ai_socktype = SOCK_STREAM;
	
	if((rv = getaddrinfo(hostname, "http", &hints, &servinfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}
	//loop through all the results and connect to the first e can
	for(p= servinfo; p != NULL; p = p-> ai_next)
	{
		h = (struct sockaddr_in *) p ->ai_addr;
		strcpy(ip, inet_ntoa(h->sin_addr));
	}
	
	freeaddrinfo(servinfo); //all done 

	return 0;
}
