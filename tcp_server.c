#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

int main(){
	char server_mssg[256] = "Hooo I am the server mssg, hooo I came form underground";
	
	//create the server socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	//define server structure
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY; // this const resolves to any IP address on the local machine
	
	// bind the socket to the specified IP and port, ie listen function
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

	listen(server_socket, 5); //arbitary number in our case, ciz I dont plan on hving big traffic
	
	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);
	
	send(client_socket, server_mssg, sizeof(server_mssg),0); //send mssg

	close(server_socket);	

	return 0;
	
}

