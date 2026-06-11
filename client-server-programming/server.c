#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{

	int server_fd, client_fd;

	struct sockaddr_in server_addr;

	char buffer[100];

	server_fd = socket(AF_INET, SOCK_STREAM, 0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

	listen(server_fd, 5);

	printf("waiting for the client : \n");

	client_fd = accept(server_fd, NULL, NULL);

	read(client_fd, buffer, sizeof(buffer));

	printf("the message from the client is : %s\n", buffer);

	write(client_fd, "Hello client", 12);

	close(client_fd);
	close(server_fd);

	return 0;
}
