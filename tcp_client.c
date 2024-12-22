#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main(){
	// Create a socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0); //uses tcp protocol since last param is 0
	
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);// the port I wanna connect to
	server_address.sin_addr.s_addr = INADDR_ANY; //connect to 0.0.0.0

	int connection = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	 //checking for connection success
	if (connection == -1) {printf(" there is an error with the connection, is the server running?? \n");}

	char server_response[256];
    int bytes_received;
    
    while (  (bytes_received = recv(network_socket, &server_response, sizeof(server_response)-1,0))  >0){
        
        printf("received this many bytes %d\n", bytes_received);
        server_response[255] = '\0';
        printf("we got this data from server %s\n", server_response);
		char clinetmsg[256] = "hello from client\0";
		send(network_socket, &clinetmsg, sizeof(clinetmsg), 0);
    }
    if (bytes_received == -1) { perror("recv error"); }
	
	close(network_socket);
	return 0;
}
