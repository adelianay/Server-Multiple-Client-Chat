#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 5222

int main(){

    char message[1024];
    int temp;

    int cSocket = socket(AF_INET, SOCK_STREAM, 0); //create a socket
    //AF_inet protocal family for IPv4 protocols
    //sock_stream is stream socket (type of sockets) means its reliable, 2 way, connection-based service
    //if can't make socket
    if(cSocket < 0){
        printf("Make Socket Failed\n");
        exit(1);
    } else {
        printf("Client Socket Created\n");
    }

    struct sockaddr_in server_address;
    //set address
    memset(&server_address, '\0', sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    //to connect the socket to the address of the server
    temp = connect(cSocket, (struct sockaddr*)&server_address, sizeof(server_address));
    if(temp < 0){
        printf("Can't connect to server\n");
        exit(1);
    }
    printf("Connected to Server\n");
    



    while(1){

		printf("Client: \t");
		scanf("%s", &message[0]);
		send(cSocket, message, strlen(message), 0);

		if(strcmp(message, ":exit") == 0){
			close(cSocket);
			printf("Disconnected from server.\n");
			exit(1);
		}

        //recv() function returns the lengths of message in bytes, 0 means no messages are available
		if(recv(cSocket, message, 1024, 0) < 0){ 
			printf("Error in receiving data.\n");
		}else{
			printf("Server: \t%s\n", message);
		}
	}

    return 0;

}