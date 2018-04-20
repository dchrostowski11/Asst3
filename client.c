#include <stdio.h>
#include <stdlib.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

int main (){

	//create the socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	//specify an address for the socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	int connection_status = connect(network_socket, (struct sockaddr *)&server_address, sizeof(server_address));
	
	//check for error with connection
	if (connection_status == -1){
		printf("There was an error making a connection to the remote socket!\n");
	}
	
	//receive data from the server
	char server_response[256];
	recv(network_socket, &server_response, sizeof(server_response), 0);
	
	//print out the server's response
	printf("The server sent the data: %s\n", server_response);
	
	//finally close the socket
	close(network_socket);
	
	return 0;
}  



/*
#include "csapp.h"

	//	int socket(int domain, int type, int protocol);  
	//		returns nonnegative descriptor if OK, -1 on error
	//		clientfd = Socket(AF_INET, SOCK_STREAM, 0);
	
	//	int connect( int sockfd, struct sockaddr *serv_addr, int addrlen );
	//		returns 0 if OK, -1 on error
	//		socket address is serv_addr, addrlen is sizeof(sockaddr_in)	

	//	int open_cliendfd(char * hostname, int port);
	//		returns descriptor if OK, -1 on Unix error, -2 on DNS error
	// 		establises connection w/ a server running on host hostname

int open_clientfd(char * hostname, int port){
	
	int clientfd;
	struct hostent *hp;
	struct sockaddr_in serveraddr;
	
	//check for errors
	if((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		return -1;
	}
	
	if ((hp = gethostbyname(hostname)) == NULL){
		return -2;
	}
	
	bzero((char *) &serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	bcopy((char *)hp->h_addr_list[0], (char *)&serveraddr.sin_addr.s_addr, hp->h_length);
	serveraddr.sin_port = htons(port);
	
	if(connect(clientfd, (SA *) &serveraddr, sizeof(serveraddr)) < 0){
		return -1;
	}
	
	return clientfd;
	
}
*/







