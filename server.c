#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

int main(){
	
	char server_message[256] = "You have reached the server!";
	
	//create the server socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	//define the server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	//bind the socket to out specified IP and port
	bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
	
	
	listen(server_socket, 1024);
	
	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);
	
	//send the message
	send(client_socket, server_message, sizeof(server_message), 0);

	//close the socket
	close(server_socket);
	return 0;
}




/*#include "csapp.h"

	//	int bind(int sockfd, struct sockaddr *my_addr, int addrlen)
	//		returns 0 if OK, -1 on error
	//		bind tells the kernel to associate server's socket address in my_addr w/ the
	//			socket descriptor sockfd.  addrlen is sizeof(sockaddr_in)
	
	//	int listen(int sockfd, int backlog);
	//		returns 0 if OK, -1 on error
	//		converts sockfd from an active socket to a listening socket that can accept 
	//			connection requests from clients
	//		backlog is a hint about the number of outstanding connections requests that 
	//			the kernel should queue up before it starts to refuse requests
	//			typically set to a large value such as 1024
	
	//	int open_listenfd(int port)
	//		returns descriptor if OK, -1 on UNIX error
	//		opens and returns a listening descriptor that is ready to receive connection
	//			requests on the port: port	
	
	
int open_listenfd(int port){
	int listen fd, optval = 1;
	struct sockaddr_in serveraddr;
	
	// create a socket descriptor
	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		return -1;
	}
	
	if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int)) < 0){
		return -1;
	}
	
	bzero((char *) &serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons((unsigned short)port);
	if(bind(listenfd, (SA *)&serveraddr, sizeof(serveraddr)) < 0){
		return -1;
	}
	
	if(listen(listen fd, LISTENQ) < 0){
		retrun -1;
	}
	
	return listenfd;
}

	//	int accept(int listenfd, struct sockaddr *addr, int *addrlen)
	//		returns nonnegative connected descriptor if OK, -1 on error
	//		waits for a connection request from a client to arrive on listening descriptor listenfd, 
	//			then fills in the client socket address in addr and returns a connected descriptor	
	//			that can be used to communicate with the client using UNIX I/O functions
	
	
	
	*/
	
