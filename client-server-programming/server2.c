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

    bind(server_fd, (struct sockaddr *)&server_addr,
         sizeof(server_addr));

    listen(server_fd, 5);

    printf("waiting for client...\n");

    //client_fd = accept(server_fd, NULL, NULL);

    while(1)
    {
    	client_fd = accept(server_fd, NULL, NULL);

        memset(buffer, 0, sizeof(buffer));

        read(client_fd, buffer, sizeof(buffer));

        printf("client : %s\n", buffer);

        if(strcmp(buffer, "exit\n") == 0)
            break;

        printf("server : ");
        fgets(buffer, sizeof(buffer), stdin);

        write(client_fd, buffer, strlen(buffer));

        if(strcmp(buffer, "exit\n") == 0)
            break;
    }

    close(client_fd);
    close(server_fd);

    return 0;
}
