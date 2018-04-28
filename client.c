#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>

#define PORT "9878"

int netserverinit(char *hostname){
	
	struct addrinfo hints, *result;
	int rc;
	
	memset(&hints, 0, sizeof(struct addrinfo));
	//hints.ai_protocol = AF_INET;
	hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
	hints.ai_socktype = SOCK_STREAM;

	
	rc = getaddrinfo(NULL, PORT, &hints, &result);
	if(rc != 0){
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rc));
        return -1;
    }
	freeaddrinfo(result);
	
	printf("hostname: %s exists!\n", hostname);	    
    return 0;	
}

int netopen(const char *pathname, int flags){
/*
	Includes one of the following access modes: O_RDONLY, 0_WRONLY, O_RDWR
	
	Returns a new file descriptor(negative number < -1) or -1 on error
*/
	//const char *file_path;
	const char *access_mode;
	
	if(flags == O_RDONLY){
		access_mode = "O_RDONLY";
	} else if(flags == O_WRONLY){
		access_mode = "O_WRONLY";
	} else if(flags == O_RDWR){
		access_mode = "O_RDWR";
	} else {
		fprintf(stderr, "flags must be one of the following: O_RDONLY, 0_WRONLY, O_RDWR\n");
		return -1;
	}
	
	printf("access mode is: %s\n", access_mode);	
	
	int openSocket, openAddr;
	struct addrinfo hints, *servinfo, *p;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	
	openAddr = getaddrinfo(NULL, PORT, &hints, &servinfo);
	if(openAddr != 0){
		fprintf(stderr,"getaddrinfo:%s\n", gai_strerror(openAddr));
		return -1;
	}
	
	for(p = servinfo; p != NULL; p = p->ai_next){
		openSocket = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if(openSocket == -1){
			fprintf(stderr, " failed creating socket!\n");
			continue;
		}
		if(connect(openSocket, p->ai_addr, p->ai_addrlen) == -1){
			perror("connect");
			close(openSocket);
			continue;
		}
		
		break;
	}
	
	if(p == NULL){
		fprintf(stderr, "failed to connect\n");
		return -1;
	}
	
	freeaddrinfo(servinfo);
		
	
	
	/*	
	openSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(openSocket != 0){
		fprintf(stderr, "failed creating socket!\n");
		return -1;
	} */
	return 0;
}


int main() {

	int socket_fd = netserverinit("basic.cs.rutgers.edu");
	if (socket_fd != 0){
		fprintf(stderr, "please use a hostname that exists!\n");
		return -1;
	}
	
	int netfd = netopen("/.autofd/ilab/ilab_users/deymious/test.c", O_RDONLY);
	printf("netfd = %d\n", netfd);

	return 0;
}
