#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include <unistd.h> // for close

int main(){
	//create the server socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	//define server structure
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY; // this const resolves to any IP address on the local machine
	
	// bind the socket to the specified IP and port, and listen for clients
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	listen(server_socket, 5); //5 is an arbitary number
	
	// the client socket is different from the listening socket.
	// the listening socket takes connections from clients and 
	// after a connection is accepted, that client talks with the server
	// with the the accept socket and keeps the listen socket free for other 
	// clients to connect.
	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);
	int msg = 1;
    while(1){
        printf("sending %d\n", msg);
        char server_mssg[256];
        char clientreply[256];
        sprintf(server_mssg, "%d", msg);
    	send(client_socket, server_mssg, sizeof(server_mssg),0); 
        msg = msg*9;

	int bytesrec = recv(client_socket, &clientreply, sizeof(clientreply),0);
	if (bytesrec == -1){
		printf("error receiving from client\n");
	}
	else {
		printf("%s\n", clientreply);
	}

        sleep(1);
    }

	close(server_socket);	

	return 0;
	
}
