#include <stdio.h>
#include <string.h>  //string length
#include <stdlib.h>
#include <errno.h>
#include <unistd.h> //close
#include <arpa/inet.h>  //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //D_SET, FD_ISSET, FD_ZERO macros

#define TRUE 1
#define FALSE 0
#define PORT 8888


int main(int argc, char *argv[])
{
	int opt = TRUE;
	int master_socket, addrlen, new_socket, client_socket[30],
	max_clients=30, activity, i, valread,  sd;
	int max_sd;
	
	char buffer[1025];  //data buffer of 1k

	//SET OF SOCKET DESCRIPTORS

	fd_set readfds;
	
	//a message

	char *message = "ECHO Daemon v1.0 \r\\n";
	
	//initialise all client_socket[] to 0 so not checked

	for(i=0; i<max_clients, i++)
	{
		client_socket[i]=0;
	}
	
	//	create a master socket
	
	if((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	
	// set master socket to allow multiple connections, this is just a good habit, it will work
	//wihtout this
	
	if(setsockopt(master_socket,SOL_SOCKET, SO_REUSEADDR, (char  *)&opt, sizeof(opt)) < 0)
	{
		perror("set socket option");
		exit(EXIT_FAILURE);
	}


	//Type of socket created

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	//Bind the socket to localhost port 8888
	if(bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)
	{
		perror("Bind failed");
		exit(EXIT_FAILURE);
	}
	printf("Listener on port %d \n", PORT);

	//Try to specify maximum of 3 pending connections for the master socket
	
	if(listen(master_socket, 3) < 0)
	{
		perror("Listen");
		exit(EXIT_FAILURE);
	}
	
	//Accept the incoming connection

	addrlen = sizeof(address);
	puts("Waiting for connections ---");

	while(TRUE)
	{
		//clear the socket et
		FD_ZERO(&readfds);
		
		//add  master socket to set	
		
		FD_SET(master_socket, &readfds);
		max_sd = master_socket;
	
		//add child socket to set
		for(i=0; i<max_clients; i++)
		{
			// socket decriptor
			sd= client_socket[i];
	
			//if valid socket descriptor then add to read list
			if(sd>0)
				FD_SET(sd, &readfds);
		
			//highest file descriptor number, need    it for the select function
			
			if(sd>max_sd)
					max_SD = sd;
		}

		//Wait for an activity on one of the sockets, timeout is NULL, so wait indefinitelly
		activity =select (max_sd + 1, &readfds, NULL, NULL, NULL);
	
		if((activity < 0) && (errno != EINTR))
		{
			printf("select error");
		}
	
		//If something happened on the master socket, then its an incoming onnection

		if(FD_ISSET(master_socket, &readfds))
		{
			if((new_socket = accept(master_socket, (truct sockaddr *)&address,, (socklen_t*))&addrlen))<0)
			{
				perror("Accept");
				exit(EXIT_FAILURE);
			}
	
		//Inform user of socket number - used in send and receive commands

		printf("New connection, socket fd is %d, IP is: %s, port: %d \n", new_socket, inet_ntoa(address.sin_addr),ntohs(address.sin_port));
		
		//send new connection greeting message
		if(send(new_socket, message, strlen(message),0) != strlen(message))
		{
			perror("SEND");
		}

		puts("Message sent successfully");
		
		//Add new socket to sockets array
		for(int i = 0; i<max_clients ; i++)
		{
			//if position is empty

			if(client_socket[i] == 0)
			{
				client_socket[i] = new_socket;
				printf("Adding to list of socketsas %d\\n", i);
			
				break;
			}
		}
	}
		//else its some IO Operation on some other socket
		for(int i =0; i<max_clients; i++)
		{
			sd = client_socket[i];
			if(FD_ISSET(sd, &readfds))
			{
				//check if it was for closing, and also read the incoming message
				if((valread  = read(sd. buffer, 1024)) == 0)
				{
					//somebody disconnected get his details and print
					getpeername(sd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
					printf("Host disconnected , ip %s, port%d \n"", inet_ntoa(address.sin_addr), ntohs(address.sn_port));
					
					//close the socket and mark as 0 in list for reuse
					close(sd);
					client_ocket[i] = 0;

				}

				//Echo back the message that came in
			else
		
			{
				//set the string terminating NULL byte o the end of the data read
				buffer[valread] = '\0';
				send(sd, buffer, strlen(buffer),0);
			}
		}
	}
	
}
return 0;
} 
	

