#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

/*
	This program runs on a separate iLab machine other than that which the client code runs on.
		
	Listens for client requests from the client socket and handles those requests.  The port
	must be greater than 8k(2^13) but less than 64k(2^16). It can be hard-coded.
	
	Creates threads to run requests and passes the client socket the result of those requests... the responses 
	can be: success + data or an error code and error values
	
	Should assign each client a unique file descriptor to tell them apart
	
	Only needs to support the flags: O_RDONLY, O_WRONLY, and O_RDWR... all other flags should be an error
	
*/



int main(int argc, char **argv){

	// create a socket for the server
	int s;
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	if(server_socket < 0){
		perror("problem creating socket!");
		return -1;
	}
	
	struct addrinfo hints, *res;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	
	s = getaddrinfo(NULL, "9878", &hints, &res);
	if(s != 0){
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(1);
    }
	
	if (bind(server_socket, res->ai_addr, res->ai_addrlen) != 0){
		perror("bind issue");
		exit(1);
	}
	
	if(listen(server_socket, 10) != 0){
		perror("listening...");
		exit(1);
	}
	
	struct sockaddr_in *result_addr = (struct sockaddr_in *) res->ai_addr;
    printf("Listening on file descriptor %d, port %d\n", server_socket, ntohs(result_addr->sin_port));
    
    printf("Waiting for connection...\n");
    int client_fd = accept(server_socket, NULL, NULL);
    printf("Connection made: client_fd=%d\n", client_fd);
    
    char buf[1000];
    int len = read(client_fd, buf, sizeof(buf) - 1);
    buf[len] = '\0';
    
    printf("read %d chars\n", len);
    printf("===\n");
    printf("%s\n", buf);
    
	
	


	return 0;
}
