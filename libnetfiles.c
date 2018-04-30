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

int netopen(const char* pathname, int flags){
	//make sure that you find host	
	struct sockaddr_in addr;

	int client_socket = socket(AF_INET, SOCK_STREAM, 0);

	if(client_socket <0){
		perror("error creating socket");
		return -1;
	}
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9886);
	
	if(connect(client_socket, (struct sockaddr*) &addr, sizeof(addr))<0){

		perror("could not connect");
		return -1;
	} 

	char buf[strlen(pathname) + 10 + 2];

	buf[0] = 'O';
	buf[1] = '&';
	int i;
	for(i = 0; i<strlen(pathname); ++i){
		buf[2+i] = pathname[i];
	}

	buf[i+2] = '&';
	buf[i+3] = flags + '0';

	if(send(client_socket, buf, strlen(buf), 0)<0){
		perror("failed to sed");
		return -1;
	}

	int k = 0;
	if(read(client_socket, &k, sizeof(k)) < 0){
		perror("reading error");
	}
	
	if(k>0){
		close(client_socket);
		return ntohl(k);
	}else{
		perror("invalied file desciptor");
		return -1;
	}
}	


int main(int argc, char** argv){
	if(argc!=2){
		perror("not enough arguments");
		return -1;
	}

	int fd = netopen(argv[1], 1);
	printf("FILE DESCRIPTOR: %d\n", fd);
	return 0;

}
twork_socket);
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
