#import <stdio.h>
#import <stdlib.h>

#import <sys/types.h>
#import <sys/stat.h>
#import <fcntl.h>

/*
	This program runs on a separate iLab machine other than that which the client code runs on.
		
	Listens for client requests from the client socket and handles those requests.  The port
	must be greater than 8k(2^13) but less than 64k(2^16). It can be hard-coded.
	
	Creates threads to run requests and passes the client socket the result of those requests... the responses 
	can be: success + data or an error code and error values
	
	Should assign each client a unique file descriptor to tell them apart
	
	Only needs to support the flags: O_RDONLY, O_WRONLY, and O_RDWR... all other flags should be an error
	
*/


