/** server.c
* Ref: https://www.geeksforgeeks.org/socket-programming-cc/
* How to compile & run?
* Compile: gcc server.c -o server
* Run:
* 1. Open two terminals, one for server, the other for client
* 2. Run server first in the first terminal: ./server
* 3. Then run client in the second terminal: ./client
*/

// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8888 

int main(int argc, char const *argv[]) 
{ 
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	char *hello = "Hello, my client."; 
	
	// Creating socket file descriptor 
    printf("server: I'm going to create a socket.\n");
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("server: socket failed.\n"); 
		exit(EXIT_FAILURE); 
	} 
	
	// Forcefully attaching socket to the port 8888 
    printf("server: my port number is %d.\n", PORT);
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
	{ 
		perror("server: setsockopt.\n"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Forcefully attaching socket to the port 8888 
    printf("server: I bound to port number %d now.\n", PORT);
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) 
	{ 
		perror("server: bind failed.\n"); 
		exit(EXIT_FAILURE); 
	} 

    printf("server: I am listening on port number %d , waiting for client...\n", PORT);
	if (listen(server_fd, 3) < 0) 
	{ 
		perror("server: listen.\n"); 
		exit(EXIT_FAILURE); 
	} 

    printf("server: I'm going to accept the client.\n");
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) 
	{ 
		perror("server: accept.\n"); 
		exit(EXIT_FAILURE); 
	} 


	valread = read( new_socket , buffer, 1024); 
	printf("server:  The client said '%s' to me.\n",buffer ); 
	send(new_socket , hello , strlen(hello) , 0 ); 
	printf("server: I replied with message '%s'\n", hello); 
	return 0; 
} 
