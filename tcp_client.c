#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>

int main(){
	// Create a socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0); //uses tcp protocol tus last param is 0
	
	//specifies where the socket is going to connect to, aka address for the socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);// says the port I wanna connect to
	server_address.sin_addr.s_addr = INADDR_ANY; //connect to 0.0.0.0

	//if the connection int is -1 then there is an error with the connection
	int connection = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	 //checking for connection success
	if (connection == -1) {printf(" there is an error with the connection \n");}

	// now we gotta recieve data from the server
	char server_response[256];
	recv(network_socket, &server_response, sizeof(server_response),0);

	// print the data we got frim the server
	printf("we got this data from server %s/n", server_response);

	// close the socket
	close(network_socket);
	return 0;
}
