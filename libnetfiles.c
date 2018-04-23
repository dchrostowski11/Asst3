#include <stdio.h>
#include <stdlib.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

int netopen(const char *pathname, int flags){
	// must include one of the following access modes: O_RDONLY, O_WRONLY, O_RDWR
	// returns new file descriptor, or -1 on error
	// fd should be negative numbers but not negative 1
	int fd = -2;
	
	// check to make sure the mode is correct
	const char *access_mode;
	if(flags == O_RDONLY){
		access_mode = "O_RDONLY";
	}
	else if(flags == O_WRONLY){
		access_mode = "O_WRONLY";
	}
	else if(flags == O_RDWR){
		access_mode = "O_RDWR";
	} else {
		perror("invalid access mode!");
		return -1;
	}
	
	//make a socket
	int socket = socket(AF_INET, SOCK_STREAM, 0);
	if(socket < 0){
		perror("couldn't create socket");
	}
	
	
}

ssize_t netread(int fildes, void *buf, size_t nbyte){
	// should return a nonnegative int indicating the number of bytes actually read
	// else return -1 and set errno in the caller's context to indicate the error
}

ssize_t netwrite(int fildes, const void *buf, size_t nbyte){
	// should return the number of bytes actually written to the file associated with fildes
	// this number should never be greater than nbyte, otherwise return -1 and set errno
}

int netclose(int fd){
	// returns zero on success,
	// returns -1 on error and errno is set
}
