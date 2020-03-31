/** server.c
* Ref: https://www.geeksforgeeks.org/socket-programming-cc/
* How to compile & run?
* Compile: gcc client.c -o client
* Run:
* 1. Open two terminals, one for server, the other for client
* 2. Run server first in the first terminal: ./server
* 3. Then run client in the second terminal: ./client
*/

// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8888 

int main(int argc, char const *argv[]) 
{ 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	char *hello = "Hello, my server."; 
	char buffer[1024] = {0}; 

    printf("client: I'm going to create a socket.\n");
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n client: Socket creation error \n"); 
		return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nclient: Invalid address/ Address not supported \n"); 
		return -1; 
	} 

    printf("client: I'm going to connect to the server.\n");
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nclient: Connection Failed \n"); 
		return -1; 
	}


	send(sock , hello , strlen(hello) , 0 ); 
	printf("client: I said '%s' to the server.\n", hello); 
	valread = read( sock , buffer, 1024); 
	printf("client: The server replied to me with '%s'\n",buffer ); 
	return 0; 
} 
