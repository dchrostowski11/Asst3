#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
/*
 *	error codes:
 *	EACCESS: this should be used when trying to open or modify the file but the permission does not allow. This errno would be set from the server code
 *	EINTR: this is where threads come in.  
 *
 *
 * 
 */

int main(){
	int errno;
/*	if(pathname == NULL){
		errno = ENOENT;
		perror(strerror(errno));
		return -1;
	}

	const char* am;
	switch(flags){
		case 1:
			am = "O_RDONLY";
		case 2:
			am = "O_WRONLY";
		case 3:
			am = "O_RDWR";
		default:
			perror("invalid access mode");
	}
*/
	//create the socket
	int network_socket = socket(AF_INET, SOCK_STREAM, 0);

	//specify an address for the socket
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9878);
	addr.sin_addr.s_addr = INADDR_ANY;
	
	//call the connect function
	int connection = connect(network_socket, (struct sockaddr *) &addr, sizeof(addr));
	if(connection == -1){
		perror("Unable to connect");
		return -1;
	}

	int file_descriptor = 0;
	
	printf("The server sent this data: %d\n", file_descriptor);
	close(network_socket);
	return file_descriptor;
}

/*ssize_t netread(int fildes, void * buf, size_t nbytes){
	int network_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(9878);
	address.sin_addr.s_addr = INADDR_ANY;
	
	//call the connect function
	int connection = connect(network_socket, (struct sockaddr *) &address, sizeof(address));

	if(connection == -1){
		perror("Unable to connect");
		exit(0);
	}

	int num_bytes;
	recv(network_socket, &num_bytes, sizeof(num_bytes), 0);

	if(num_bytes<0){
		perror("Invalid amount of bytes\n");
		return -1;
	}else{
		return num_bytes;
	}
}

ssize_t netwrite(int fildes, const void * buf, size_t nbytes){
	
	int network_socket = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(9878);
	address.sin_addr.s_addr = INADDR_ANY;
	
	int connection = connect(network_socket, (struct sockaddr *) &address, sizeof(address));

	if(connection == -1){
		perror("unable to connect\n");
		return -1;
	}
	
	int num_bytes;
	recv(network_socket, &num_bytes, sizeof(num_bytes), 0);
	
	int errno;
	if(num_bytes<nbytes){
		errno= EBADF;
		perror(strerror(errno));
		return -1;
	}else{
		return num_bytes;
	}
}

int netclose(){
	return 0;
}

int netserverinit(char * hostname){
	int check;
	//need to create two addrinfo structs
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(9878);
	address.sin_addr.s_addr = INADDR_ANY;
	
	struct sockaddr_in sec_address;
	sec_address.sin_family = AF_INET;
	sec_address.sin_port = htons(9878);
	sec_address.sin_addr.s_addr = INADDR_ANY;
	if((check = getaddrinfo(hostname, 9878, address, sec_address))){
		//
	}

	return 0;
}*/
