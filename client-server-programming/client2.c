#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[100];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&server_addr,
            sizeof(server_addr));

    while(1)
    {
        printf("client : ");
        fgets(buffer, sizeof(buffer), stdin);

        write(sockfd, buffer, strlen(buffer));

        if(strcmp(buffer, "exit\n") == 0)
            break;

        memset(buffer, 0, sizeof(buffer));

        read(sockfd, buffer, sizeof(buffer));

        printf("server : %s\n", buffer);

        if(strcmp(buffer, "exit\n") == 0)
            break;
    }

    close(sockfd);

    return 0;
}
