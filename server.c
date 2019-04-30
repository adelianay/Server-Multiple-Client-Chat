#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h> 
#include <sys/types.h>  
#include <netinet/in.h> 
#include <arpa/inet.h>

#define PORT 5222

int main()
{

	// variables
	int servsock, temp, newServsock;
	
	struct sockaddr_in server_address;
	struct sockaddr_in newAddress;

	socklen_t addr_size;

	char message[1024]; //the server will read characters froom the socket connection into i=this buffer
	pid_t pidc; //pid = process ID number

	//create server socket
	servsock = socket(AF_INET, SOCK_STREAM, 0);
	if(servsock < 0 )
	{
		printf("Connection error\n");
		exit(1);
	}
	printf("Server Socket is created.\n");

	
	//define the server address
	memset(&server_address, '\0', sizeof(server_address));
	
	server_address.sin_family = AF_INET; //it contains a code for the address family, the AF_INET is a constant
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // in this, it contains the IP address of the machine on which the server is running and the INADDR_ANY is a constant
	server_address.sin_port = htons(PORT); //contains the port number. using the htons to convert port number to network byte order.
	
	//binding the socket to specified IP and port
	temp = bind(servsock, (struct sockaddr*)&server_address, sizeof(server_address));
	if(temp < 0)
	{
		printf("Binding Error\n");
		exit(1);
	}
	printf("Bind to port.. %d\n", 5222);

	//listen for incoming conection
	if(listen(servsock, 5) == 0) //5 because we only allow to connect to 5 clients
	{
		printf("Listening..\n");
	} else {
		printf("Error\n");
	}

	//accepting an incoming connection, obtaining new socket
	while(1)
	{
		
		newServsock = accept(servsock, (struct sockaddr*)&newAddress, &addr_size); //accept the connection from the client
		if(newServsock < 0)
		{
			exit(1);
		}
		printf("Connection from %s: %d\n", inet_ntoa(newAddress.sin_addr), ntohs(newAddress.sin_port));

		if((pidc = fork()) == 0) //new process for connection
		{
			close(servsock);

			//receiving the messages from the client
			while(1)
			{
				recv(newServsock, message, 1024, 0);
				if(strcmp(message, ":exit") == 0)
				{
					printf("Disconnected from %s:%d\n", inet_ntoa(newAddress.sin_addr), ntohs(newAddress.sin_port));
					//inet_ntoa is converting the internet host address in network byte to string in IPv4.
					//ntohs converts the unsigned short integer frm network byte order to host byte order.
					break;
				}else{
					printf("Client: %s\n", message);
					send(newServsock, message, strlen(message), 0);
					bzero(message, sizeof(message));
				}
			}
		}
	}

	//close a socket
	close(newServsock);
	return 0;
}